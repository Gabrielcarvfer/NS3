from math import * 

#10 UEs positions in a semi-circle around the PU
semiCircleRadius = 30e3

puCoordinates = {
	"x": 75e3,
	"y": 75e3
}

for angle in range(90,180,9):
    print("%f,\n%f,\n" % (puCoordinates["x"]+semiCircleRadius*cos(pi*angle/180), puCoordinates["y"]-semiCircleRadius*sin(pi*angle/180)))