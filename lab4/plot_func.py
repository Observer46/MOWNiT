import matplotlib.pyplot as plt
import numpy as np
import sys

# if len(sys.argv) is not 2:   
#     print("Need only plot data as argument: python3 plot.py plot_data.txt")
x, y = np.loadtxt(sys.argv[1], delimiter=' ', unpack=True)
if len(sys.argv) > 2:
    interpolated_values = sys.argv[2]
    interpolation_name = sys.argv[3]
    N = sys.argv[4]
    inter_x, inter_y = np.loadtxt(interpolated_values, delimiter=' ', unpack=True)
else:
    interpolation_name = ""
    N = ""

plt.plot(x, y, label='')

plt.xlabel('x')
plt.ylabel('f(x)')
plt.title('f(x) = exp(3*cos(4*x)) ' if len(sys.argv) == 2 else interpolation_name + " N=" + N)
if len(sys.argv) > 2:
    plt.plot(inter_x, inter_y, label = "Interpolated", color = 'r')

plt.legend()
plt.show()