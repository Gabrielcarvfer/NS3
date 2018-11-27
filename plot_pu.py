import matplotlib.pyplot as plt
import numpy
bufferFile = ""
with open("./build/bin/output.txt",'r') as file:
    bufferFile = file.readlines()

fig = plt.figure()
ax = plt.axes()

x = list(range(0,4999,1))

for ue_str in bufferFile:
    y = ue_str.split(sep=':')[1].replace(" ","").replace("\n","")
    y_ue = [ float(k) for k in y]
    ax.plot(x,y_ue)
    fig.show()
    pass


pass