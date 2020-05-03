import matplotlib.pyplot as plt
import numpy as np
import sys

# argv[] : 1 -> plot_name, 2 -> function_data, | 3 -> sample_data, | 4 -> approximated_data ( 5 -> approximation_name)
print("argv[] : 1 -> plot_name, 2 -> function_data, | 3 -> sample_data, | 4 -> approximated_data")
plot_name = sys.argv[1]
x, y = np.loadtxt(sys.argv[2], delimiter=' ', unpack=True)
plt.plot(x, y, label='')
plt.xlabel('x')
plt.ylabel('y')

if len(sys.argv) > 3:
    sample_x, sample_y = np.loadtxt(sys.argv[3], delimiter=' ', unpack=True)
    plt.scatter(sample_x, sample_y, color = 'g')

if len(sys.argv) > 4:
    approx_x, approx_y = np.loadtxt(sys.argv[4], delimiter=' ', unpack=True)
    plt.plot(approx_x, approx_y, label = "Approximated", color = 'r')

plt.title(plot_name)
plt.legend()
plt.show()