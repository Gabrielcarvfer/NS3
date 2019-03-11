#!/usr/bin/python3
import matplotlib.pyplot as plt
import numpy as np
import scipy.stats as stats
import statistics
import math
import numba

def plot_loss_n_shaddow(standalone_plot=False):
    bufferFile = ""

    with open("./build/bin/loss_n_shadow.txt",'r') as file:
        bufferFile = file.readlines()

    plt.ioff()


    prop_models_dict = {}
    maxSinr = -10000000
    for prop_model_str in bufferFile:
        y      = prop_model_str.replace("\n","").split(sep=' ')
        prop_model     = y[0]
        loss   = float(y[1])
        shadow = float(y[2])
        shadow2 = float(y[3])


        if prop_model not in prop_models_dict.keys():
            #Create registry
            prop_models_dict[prop_model] = {}
            prop_models_dict[prop_model]["pathloss"] = []
            prop_models_dict[prop_model]["shadow"] = []
            prop_models_dict[prop_model]["shadow2"] = []
            pass

        prop_models_dict[prop_model]["pathloss"] += [ loss ]
        prop_models_dict[prop_model]["shadow"]   += [ shadow ]
        prop_models_dict[prop_model]["shadow2"]   += [ shadow2 ]
        pass


    #print(prop_models_dict)


    minLen = 1000000
    for prop_model in prop_models_dict:
        prop_modelLen = len(prop_models_dict[prop_model]["pathloss"])
        if prop_modelLen < minLen:
            minLen = prop_modelLen


            pass
        pass

    x = list(range(0, minLen, 1))

    fig, ax = plt.subplots(nrows=1, figsize=(3,3))

    all_samples_shadow = []
    all_samples_shadow2 = []

    for prop_model in prop_models_dict:

        all_samples_shadow += prop_models_dict[prop_model]["shadow"]
        all_samples_shadow2 += prop_models_dict[prop_model]["shadow2"]


        print("Propagation model",
            prop_model,
            " mean ",
            statistics.mean(prop_models_dict[prop_model]["shadow"]),
            " stdDev ",
            statistics.stdev(prop_models_dict[prop_model]["shadow"]),
            " mean2 ",
            statistics.mean(prop_models_dict[prop_model]["shadow2"]),
            " stdDev ",
            statistics.stdev(prop_models_dict[prop_model]["shadow2"]),
            )

        samples = np.array(prop_models_dict[prop_model]["shadow"][:minLen])
        mean = np.mean(samples)
        var = np.var(samples)
        std = np.sqrt(var)

        x = np.linspace(min(samples), max(samples), 12)
        y_pdf = stats.norm.pdf(x, mean, std)

        samples1 = np.array(prop_models_dict[prop_model]["shadow2"][:minLen])
        mean1 = np.mean(samples1)
        var1 = np.var(samples1)
        std1 = np.sqrt(var1)

        x = np.linspace(min(samples), max(samples), 100)
        x1 = np.linspace(min(samples1), max(samples1), 100)

        y_pdf  = stats.norm.pdf(x, mean, std)
        y1_pdf = stats.norm.pdf(x1, mean1, std1)
        y2_pdf = stats.norm.pdf(x, 0.0, 4.47)

        ax.plot(x,y_pdf,color="blue", label="Shadowing NS3 lognormal PDF")
        #ax.plot(x1,y1_pdf,color="green", label="Shadowing std::lognormal PDF")
        ax.plot(x,y2_pdf,color="red", label="Expected PDF")
        plt.show(block=False)

        """ax.set_xlabel('tick', )
        ax.set_ylabel('pathloss (dB)')
        ax.tick_params('y')
        ax2.set_xlabel('tick')
        ax2.set_ylabel('shadow (dB)')
        ax2.tick_params('y')
        ax3.set_xlabel('valprop_model')
        ax3.set_ylabel('freq')
        ax3.tick_params('y')
        ax4.set_xlabel('tick')
        ax4.set_ylabel('shadow (dB)')
        ax4.tick_params('y')
        ax5.set_xlabel('valprop_model')
        ax5.set_ylabel('freq')
        ax5.tick_params('y')
        ax.plot(x,prop_models_dict[prop_model]['pathloss'][:minLen],alpha=0.5)
        ax2.plot(x,prop_models_dict[prop_model]["shadow"][:minLen],alpha=0.5)
        ax3.hist(prop_models_dict[prop_model]["shadow"],alpha=0.5)
        ax4.plot(x,prop_models_dict[prop_model]["shadow"][:minLen],alpha=0.5)
        ax5.hist(prop_models_dict[prop_model]["shadow"],alpha=0.5)
        plt.show(block=False)
        """
        #plt.savefig("%s.jpg" % prop_model)
        pass


    print(  "Propagation model ",
            "all",
            " mean ",
            statistics.mean(all_samples_shadow),
            " stdDev ",
            statistics.stdev(all_samples_shadow),
            " mean2 ",
            statistics.mean(all_samples_shadow2),
            " stdDev ",
            statistics.stdev(all_samples_shadow2),
            )

    samples = np.array(all_samples_shadow)
    mean = np.mean(samples)
    var = np.var(samples)
    std = np.sqrt(var)

    x = np.linspace(min(samples), max(samples), 12)
    y_pdf = stats.norm.pdf(x, mean, std)

    samples1 = np.array(all_samples_shadow2)
    mean1 = np.mean(samples1)
    var1 = np.var(samples1)
    std1 = np.sqrt(var1)

    x = np.linspace(min(samples), max(samples), 12)
    x1 = np.linspace(min(samples1), max(samples1), 12)

    y_pdf  = stats.norm.pdf(x, mean, std)
    y1_pdf = stats.norm.pdf(x1, mean1, std1)
    y2_pdf = stats.norm.pdf(x, 0.0, 4.47)

    #ax2.plot(x,y_pdf,color="cyan", label="Shadowing NS3 lognormal PDF")
    #ax2.plot(x1,y1_pdf,color="olive", label="Shadowing std::lognormal PDF")
    #ax2.plot(x,y2_pdf,color="magenta", label="Expected PDF")
    #plt.show(block=False)

    mu=0.0
    sigma=4.47

    #m_lambda 0.15533287979274613
    def range_pathloss(distance, range=False, shadowing=False, shadow=0.0, m_lambda=0.14141153679245283, m_systemLoss=1, M_PI=math.pi, m_kValue = 29.38, mu=0.0, sigma=4.47):
        numerator = m_lambda * m_lambda
        denominator = 16 * M_PI * M_PI * distance * distance * m_systemLoss;
        lossDb = -10 * math.log10 (numerator / denominator);
        if range:
            lossDb += m_kValue
            if shadowing:
                lossDb += shadow

        return lossDb


    pathloss_x = list(range(1,10000, 10))
    shadows = np.random.normal(mu, sigma, size=len(pathloss_x))

    @numba.jit
    def get_pathloss_for_ranges(pathloss_x, range, shadowing):
        pathloss_range = [0]*len(pathloss_x)
        for x in numba.prange(len(pathloss_x)):
            pathloss_range[x] = range_pathloss(distance=pathloss_x[x], range=range, shadowing=shadowing, shadow=shadows[x])
        return pathloss_range


    pathloss_fspl = get_pathloss_for_ranges(pathloss_x, False, False)
    plt.plot(pathloss_x, pathloss_fspl, color="blue", label="FSPL pathloss")

    pathloss_range_noshadow = get_pathloss_for_ranges(pathloss_x, True, False)
    plt.plot(pathloss_x, pathloss_range_noshadow, color="green", label="5G-RANGE pathloss without shadowing")

    pathloss_range_shadow = get_pathloss_for_ranges(pathloss_x, True, True)
    plt.scatter(pathloss_x, pathloss_range_shadow, color="red", alpha=0.5, label="5G-RANGE pathloss with shadowing")

    legend = plt.legend(loc='lower center', shadow=True, fontsize='large')
    plt.ylabel("Pathloss [dB]")
    plt.xlabel("Distance [m]")

    plt.show(block=False)
    pass


if __name__ == "__main__":
    print_shadow_n_loss(standalone_plot=True)
    input()
    pass
