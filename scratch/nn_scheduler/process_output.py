import matplotlib.pyplot as plt
import json

def read_json_file(file):
    #Load json
    read_json = []
    with open(file, encoding='utf-8') as json_data:
        read_json = json.load(json_data)
    return read_json

def f2s(key):
    return "%.2f" % key

def print_allocation_map(allocation_map):
    #Load RBs number and RBG size
    rbg_size = allocation_map["data"][f2s(allocation_map["keys"][0])]["rbg_size"]
    rb_num = rbg_size * allocation_map["data"][f2s(allocation_map["keys"][0])]["resource_blocks"]
    rbg_list = [i for i in range(int(rb_num/rbg_size))]
    rbg_start_list = [i*rbg_size for i in rbg_list]
    offset = allocation_map["keys"][1] - allocation_map["keys"][0]

    #Configure plot
    fig, ax = plt.subplots()
    ax.set_ylim(0, rb_num)
    ax.set_xlim(0, 100)
    ax.set_xlabel('% of simulation')
    ax.set_ylabel('rbgs (1 rbg = %d rbs)' % rbg_size)
    ax.set_yticks(rbg_start_list)
    ax.set_yticklabels(rbg_list)
    ax.grid(True)

    facecolors=['maroon',
                'brown',
                'olive',
                'teal',
                'navy',
                'orange',
                'lime',
                'cyan',
                'purple',
                'magenta',
                'blue',
                'red',
                'yellow',
                'green']
    #Plot scheduled slots
    #             x,x+offset   y, y+offset
    #ax.broken_barh([(0, 2)], (2,3), facecolors='blue')
    rntiColorMap = {}
    for sample in allocation_map["keys"]:

        for rnti, rntiAllocationMapPerLCId in allocation_map["data"][f2s(sample)]["allocationMapPerRntiPerLCId"].items():
            if rnti not in rntiColorMap.keys():
                rntiColorMap[rnti] = facecolors[0]
                facecolors.pop(0)
            for allocation in rntiAllocationMapPerLCId:
                x0 = sample
                y0 = allocation["rb_index"]
                ax.broken_barh([(x0, offset)], (y0*rbg_size, rbg_size), facecolors=rntiColorMap[rnti])
                pass
            pass

        pass

    plt.show()
    return
