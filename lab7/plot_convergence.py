import matplotlib.pyplot as plt
import numpy as np
import sys

# argv[] : 1 -> example_no|"PI"
print("argv[] : 1 -> example_no")
if len(sys.argv) < 2:
    print("Niepoprawna ilosc argumentow!")
    exit()
if sys.argv[1] == "PI":
    filename = "output/PI_convergence.txt"
    monte_x, monte_y = np.loadtxt(filename, delimiter=' ', unpack=True)
    plt.plot(monte_x, monte_y, label='Monte Carlo PI value')
    PI_x, PI_y = [], []
    for x in monte_x:
        PI_x.append(x)
        PI_y.append(np.pi)
    plt.plot(PI_x, PI_y, label = "PI value (from NumPy)", color = 'r')

    plot_name = "PI approximation using Monte Carlo"
else:
    example_no = sys.argv[1]
    example_name = "output/f" + example_no + "_"

    plot_name = "Convergence for f" + example_no

    rec_file =  example_name + "Rec.txt"
    trap_file = example_name + "Trap.txt"
    simp_file = example_name + "Simp.txt"
    monte_file = example_name + "Monte.txt"

    rec_x, rec_y = np.loadtxt(rec_file, delimiter=' ', unpack=True)
    plt.plot(rec_x, rec_y, label='Rectangle', color = 'c')

    trap_x, trap_y = np.loadtxt(trap_file, delimiter=' ', unpack=True)
    plt.plot(trap_x, trap_y, label = "Trapezoid",color = 'm')

    simp_x, simp_y = np.loadtxt(simp_file, delimiter=' ', unpack=True)
    plt.plot(simp_x, simp_y, label = "Simpson", color = 'b')

    monte_x, monte_y = np.loadtxt(monte_file, delimiter=' ', unpack=True)
    plt.plot(monte_x, monte_y, label = "Monte Carlo", color = 'k')

    expected_values = np.loadtxt("wolfram_values.txt", delimiter='\n', unpack=True)
    real_x, real_y = [], []
    for x in rec_x:
        real_x.append(x)
        real_y.append(expected_values[int(example_no) - 1])
    plt.plot(real_x, real_y, label = "Wolfram value", color = 'r')

plt.xlabel('n (iterations)')
plt.ylabel('Result')
plt.title(plot_name)
plt.legend()
plt.show()