import matplotlib.pyplot as plt
import numpy as np
import sys

# argv[] : 1 -> example_no
print("argv[] : 1 -> example_no")
if len(sys.argv) != 2:
    print("Niepoprawna ilosc argumentow!")
    exit()

example_no = sys.argv[1]
example_name = "_example_" + example_no + ".txt"

plot_name = "Convergence for SOLE - example " + example_no

jacobi_file = "Jacobi" + example_name
gauss_seidel_file = "GaussSeidel" + example_name
sor_file = "SOR" + example_name

jac_x, jac_y = np.loadtxt(jacobi_file, delimiter=' ', unpack=True)
plt.plot(jac_x, jac_y, label='Jacobi', color = 'g')
plt.xlabel('Iterations')
plt.ylabel('Distance from correct solution')


gausei_x, gausei_y = np.loadtxt(gauss_seidel_file, delimiter=' ', unpack=True)
plt.plot(gausei_x, gausei_y, label = "Gauss-Seidel",color = 'b')

sor_x, sor_y = np.loadtxt(sor_file, delimiter=' ', unpack=True)
plt.plot(sor_x, sor_y, label = "SOR", color = 'r')

plt.title(plot_name)
plt.legend()
plt.show()