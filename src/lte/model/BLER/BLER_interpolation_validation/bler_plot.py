# Source
"""
LteMiesmErrorModel::GetTbDecodificationStats

    [...]

    LoadErrorData();
    std::vector<std::string> channels = {"CDL_A", "CDL_D"};
    for (std::string tchan: channels)
        for (uint8_t tnum = 0; tnum < 6; tnum++)
            for (uint16_t tcbs = 512; tcbs <8193; tcbs*=2)
                for (uint8_t tmcs = 0; tmcs < 27; tmcs++)
                    for (double tsnr = -30.0; tsnr < 50.0; tsnr += 0.1)
                    {
                        double bler = MappingMiBler(tsnr, tmcs, tcbs, tnum, tchan);
                        std::cerr << "snr " << tsnr << " mcs " << (int)tmcs << " cbs " << (int)tcbs << " num " << (int)tnum << " chan " << tchan << " bler " << bler << std::endl;
                    }
    exit(-1);
"""
# Redirect error output to a file (e.g. program.exe 2> bler.txt)

# Output example
"""
snr -22 mcs 2 cbs 512 num 0 chan CDL_A bler 1
snr -21 mcs 2 cbs 512 num 0 chan CDL_A bler 1
snr -20 mcs 2 cbs 512 num 0 chan CDL_A bler 1
snr -19 mcs 2 cbs 512 num 0 chan CDL_A bler 1
snr -18 mcs 2 cbs 512 num 0 chan CDL_A bler 1
snr -17 mcs 2 cbs 512 num 0 chan CDL_A bler 1
snr -16 mcs 2 cbs 512 num 0 chan CDL_A bler 0.999857
snr -15 mcs 2 cbs 512 num 0 chan CDL_A bler 0.999433
snr -14 mcs 2 cbs 512 num 0 chan CDL_A bler 0.997096
snr -13 mcs 2 cbs 512 num 0 chan CDL_A bler 0.991066
snr -12 mcs 2 cbs 512 num 0 chan CDL_A bler 0.97778
snr -11 mcs 2 cbs 512 num 0 chan CDL_A bler 0.957257
snr -10 mcs 2 cbs 512 num 0 chan CDL_A bler 0.928239
snr -9 mcs 2 cbs 512 num 0 chan CDL_A bler 0.893797
snr -8 mcs 2 cbs 512 num 0 chan CDL_A bler 0.846998
snr -7 mcs 2 cbs 512 num 0 chan CDL_A bler 0.79272
snr -6 mcs 2 cbs 512 num 0 chan CDL_A bler 0.734102
snr -5 mcs 2 cbs 512 num 0 chan CDL_A bler 0.6545
snr -4 mcs 2 cbs 512 num 0 chan CDL_A bler 0.553553
snr -3 mcs 2 cbs 512 num 0 chan CDL_A bler 0.455377
snr -2 mcs 2 cbs 512 num 0 chan CDL_A bler 0.380662
snr -1 mcs 2 cbs 512 num 0 chan CDL_A bler 0.305724
snr 0 mcs 2 cbs 512 num 0 chan CDL_A bler 0.241418
snr 1 mcs 2 cbs 512 num 0 chan CDL_A bler 0.198111
snr 2 mcs 2 cbs 512 num 0 chan CDL_A bler 0.15206
snr 3 mcs 2 cbs 512 num 0 chan CDL_A bler 0.112408
snr 4 mcs 2 cbs 512 num 0 chan CDL_A bler 0.0844331
snr 5 mcs 2 cbs 512 num 0 chan CDL_A bler 0.0676408
snr 6 mcs 2 cbs 512 num 0 chan CDL_A bler 0.0551304
snr 7 mcs 2 cbs 512 num 0 chan CDL_A bler 0.0448472
snr 8 mcs 2 cbs 512 num 0 chan CDL_A bler 0.0361129
snr 9 mcs 2 cbs 512 num 0 chan CDL_A bler 0.0289246
snr 10 mcs 2 cbs 512 num 0 chan CDL_A bler 0.023313
snr 11 mcs 2 cbs 512 num 0 chan CDL_A bler 0.0192452
snr 12 mcs 2 cbs 512 num 0 chan CDL_A bler 0.0161526
snr 13 mcs 2 cbs 512 num 0 chan CDL_A bler 0.0132948
snr 14 mcs 2 cbs 512 num 0 chan CDL_A bler 0.0109165
snr 15 mcs 2 cbs 512 num 0 chan CDL_A bler 0.00904714
snr 16 mcs 2 cbs 512 num 0 chan CDL_A bler 0.00752071
snr 17 mcs 2 cbs 512 num 0 chan CDL_A bler 0.00624068
snr 18 mcs 2 cbs 512 num 0 chan CDL_A bler 0.00509029
snr 19 mcs 2 cbs 512 num 0 chan CDL_A bler 0.00397325
snr 20 mcs 2 cbs 512 num 0 chan CDL_A bler 0.00317291
snr 21 mcs 2 cbs 512 num 0 chan CDL_A bler 0.00271853
snr 22 mcs 2 cbs 512 num 0 chan CDL_A bler 0.00228846
snr 23 mcs 2 cbs 512 num 0 chan CDL_A bler 0.00171538
snr 24 mcs 2 cbs 512 num 0 chan CDL_A bler 0.00119283
snr 25 mcs 2 cbs 512 num 0 chan CDL_A bler 0
snr 26 mcs 2 cbs 512 num 0 chan CDL_A bler 0
snr 27 mcs 2 cbs 512 num 0 chan CDL_A bler 0
snr 28 mcs 2 cbs 512 num 0 chan CDL_A bler 0
"""

# Parse input
file_contents = []
with open("bler.txt", "r") as file:
    file_contents = file.readlines()

points = {}
points_per_chan_num_cbs_mcs_snr = {}
for line in file_contents:
    _, snr, _, mcs, _, cbs, _, num, _, chan, _, bler = line.split()
    snr = float(snr)
    mcs = int(mcs)
    cbs = int(cbs)
    num = int(num)
    bler = float(bler)

    points[(chan, num, cbs, mcs, snr, bler)] = None
    if chan not in points_per_chan_num_cbs_mcs_snr:
        points_per_chan_num_cbs_mcs_snr[chan] = {}
    if num not in points_per_chan_num_cbs_mcs_snr[chan]:
        points_per_chan_num_cbs_mcs_snr[chan][num] = {}
    if cbs not in points_per_chan_num_cbs_mcs_snr[chan][num]:
        points_per_chan_num_cbs_mcs_snr[chan][num][cbs] = {}
    if mcs not in points_per_chan_num_cbs_mcs_snr[chan][num][cbs]:
        points_per_chan_num_cbs_mcs_snr[chan][num][cbs][mcs] = {}
    points_per_chan_num_cbs_mcs_snr[chan][num][cbs][mcs][snr] = bler

import matplotlib.pyplot as plt

# Plot contents
for chan in points_per_chan_num_cbs_mcs_snr:
    for num in points_per_chan_num_cbs_mcs_snr[chan]:
        for cbs in points_per_chan_num_cbs_mcs_snr[chan][num]:
            plt.clf()
            title = "Channel_%s_Numerology_%d_Code_Block_Size_%d" % (chan, num, cbs)
            plt.title(title)
            for mcs in points_per_chan_num_cbs_mcs_snr[chan][num][cbs]:
                points = points_per_chan_num_cbs_mcs_snr[chan][num][cbs][mcs]
                label = "%s_num_%d_mcs_%d" % (chan, num, mcs)
                plt.plot(list(points.keys()), list(points.values()), label=label)
            plt.legend(ncol=4, fontsize='xx-small', loc="center", bbox_to_anchor=(0.5, -0.4))
            plt.ylabel("BLER")
            plt.xlabel("SINR")
            plt.savefig(title+".png")
            #plt.show()
print()