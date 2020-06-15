import matplotlib.pyplot as plt
import numpy as np
import sys

# argv[] : 1 -> file_name, 2 -> x|y|z, 3-> x|y|z
print("argv[] : 1 -> file_name, 2 -> x|y|z, 3-> x|y|z")
if len(sys.argv) != 4:
    print("Niepoprawna ilosc argumentow!")
    exit()

filename = sys.argv[1]
x_axis = sys.argv[2]
y_axis = sys.argv[3]

data_t, data_x, data_y, data_z = np.loadtxt(filename, delimiter=' ', unpack=True)
if x_axis == "x":
    plot_x = data_x
elif x_axis == "y":
    plot_x = data_y
elif x_axis == "z":
    plot_x = data_z
else:
    print("Nieznana os (pierwsza)!")
    exit()
if y_axis == "x":
    plot_y = data_x
elif y_axis == "y":
    plot_y = data_y
elif y_axis == "z":
    plot_y = data_z
else:
    print("Nieznana os (pierwsza)!")
    exit()

plot_name = "Lorenz system solution (sigma = 10, beta = 8/3, rho = 28)"
label_name = filename[7:-4] + " solution"
plt.plot(plot_x, plot_y, color = 'c', label=label_name)

plt.xlabel(x_axis)
plt.ylabel(y_axis)
plt.title(plot_name)
plt.legend()
plt.show()