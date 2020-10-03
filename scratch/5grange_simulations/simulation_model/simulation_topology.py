import random

def distanceFromCenter(x, y, z, xzero=50e3, yzero=50e3, zzero=0):
    return ((x-xzero)**2 + (y-yzero)**2 + (z-zzero)**2)**0.5

def generatePosition(xRange, yRange, zRange, cellRadius=50e3):
    if len(xRange) == 1:
        xRange = xRange[0]
    if len(yRange) == 1:
        yRange = yRange[0]
    if len(zRange) == 1:
        zRange = zRange[0]

    x = round(random.uniform(xRange[0], xRange[1]), 2)
    y = round(random.uniform(yRange[0], yRange[1]), 2)
    z = round(random.uniform(zRange[0], zRange[1]), 2)

    i = 0
    while distanceFromCenter(x, y, z) > cellRadius:
        if i == 0:
            x = round(random.uniform(xRange[0], xRange[1]), 2)
        elif i == 1:
            y = round(random.uniform(xRange[0], xRange[1]), 2)
        else:
            z = round(random.uniform(zRange[0], zRange[1]), 2)
        i = (i+1) % 3

    return x, y, z
