import numpy as np
import matplotlib.pyplot as plt

np.random.seed(19680801)

pathloss_trace = []
with open("../build/bin/pathloss.txt","r") as f:
    pathloss_trace = f.readlines()

for i in range(len(pathloss_trace)):
    pathloss_trace[i] = float(pathloss_trace[i])

fig, ax = plt.subplots(figsize=(8, 4))

# plot the cumulative histogram
n, bins, patches = ax.hist(pathloss_trace, 6, density=True, histtype='step',
                           cumulative=True, label='NS3')

from scipy import stats
# Add a line showing the expected distribution.
#y = ((1 / (np.sqrt(2 * np.pi) * sigma)) *
#     np.exp(-0.5 * (1 / sigma * (bins - mu))**2))
#y = y.cumsum()
#y /= y[-1]
#
#ax.plot(pathloss_trace, stats.norm.cdf(sorted(pathloss_trace)), 'k--', linewidth=1.5, label='Theoretical')

# tidy up the figure
ax.grid(True)
ax.set_xlim(105, 175)
ax.legend(loc='right')
ax.set_xlabel('Combined loss (dB)')
ax.set_ylabel('CDF')

plt.show()

fig.savefig("../build/bin/cdfPathloss.png")
