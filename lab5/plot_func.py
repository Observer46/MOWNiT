import matplotlib.pyplot as plt
import numpy as np
import sys

# argv[] : 1 -> approx_type, 2 -> function, 3 -> approx_degree, 4 -> function_data, | 5 -> sample_data, | 6 -> approximated_data
print("argv[] : 1 -> approx_type, 2 -> function, 3 -> approx_degree, 4 -> function_data, | 5 -> sample_data, | 6 -> approximated_data")
if len(sys.argv) < 5:
    exit()
approx_type = sys.argv[1]
func_name = sys.argv[2]
approx_degree = sys.argv[3]

plot_name = approx_type + " approximation of " + func_name + ", m = " + approx_degree

x, y = np.loadtxt(sys.argv[4], delimiter=' ', unpack=True)
plt.plot(x, y, label='')
plt.xlabel('x')
plt.ylabel('y')

if len(sys.argv) > 5:
    sample_x, sample_y = np.loadtxt(sys.argv[5], delimiter=' ', unpack=True)
    plt.scatter(sample_x, sample_y, color = 'g')

if len(sys.argv) > 6:
    approx_x, approx_y = np.loadtxt(sys.argv[6], delimiter=' ', unpack=True)
    plt.plot(approx_x, approx_y, label = "Approximated", color = 'r')

plt.title(plot_name)
plt.legend()
plt.show()