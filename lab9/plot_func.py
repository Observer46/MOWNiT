import matplotlib.pyplot as plt
import numpy as np
import sys

# argv[] : 1 -> variant_no
print("argv[] : 1 -> variant_no (default names for files are required)")
print("Exact solution - func_exact_(1|2|3).txt, func_euler_(1|2|3).txt, func_rk4_(1|2|3).txt")
if len(sys.argv) != 2:
    print("Niepoprawna ilosc argumentow!")
    exit()

variant_no = sys.argv[1]
if variant_no == "1":
    step_size = "1e-2"
elif variant_no == "2":
    step_size = "1e-3"
elif variant_no == "3":
    step_size = "1e-4"

exact_file = "func_exact_" + variant_no + ".txt"
euler_file = "func_euler_" + variant_no + ".txt"
rk_file = "func_rk4_" + variant_no + ".txt"

exact_x, exact_y = np.loadtxt(exact_file, delimiter=' ', unpack=True)
euler_x, euler_y = np.loadtxt(euler_file, delimiter=' ', unpack=True)
rk_x, rk_y = np.loadtxt(rk_file, delimiter=' ', unpack=True)


plot_name = "Euler and Runge-Knutt order 4 comparision - step size " + step_size

plt.plot(exact_x, exact_y, color = 'r', label = "Exact solution")
plt.plot(euler_x, euler_y, color = 'c', label = "Euler solution")
plt.plot(rk_x, rk_y, color = 'g', label = "RK4 solution")

plt.xlabel('x')
plt.ylabel('y')
plt.title(plot_name)
plt.legend(loc='lower left' if variant_no == "3" else 'best')
plt.show()