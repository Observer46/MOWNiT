import matplotlib.pyplot as plt
import numpy as np
import sys

filename = "output/PI_plot.txt"
print("Dane pobierane z pliku:",filename)
monte_x, monte_y, is_in = np.loadtxt(filename, delimiter=' ', unpack=True)
in_x, in_y = [], []
out_x, out_y = [], []
for i in range(len(monte_x)):
    if is_in[i]:
        in_x.append(monte_x[i])
        in_y.append(monte_y[i])
    else:
        out_x.append(monte_x[i])
        out_y.append(monte_y[i])

plt.scatter(in_x, in_y, color ='r', s=5)
plt.scatter(out_x, out_y, s=5)

plot_name = "Monte Carlo PI calculation visualization"


plt.xlabel('x')
plt.ylabel('y')
plt.title(plot_name)
plt.axis("scaled")
plt.legend()
plt.show()