import matplotlib.pyplot as plt
import numpy as np
import sys

if len(sys.argv) !=4:
    print("Needed: errors.txt interpolation_type node_type")
    exit(1)

x, y = np.loadtxt(sys.argv[1], delimiter=' ', unpack=True)


interpolation_type = sys.argv[2]
node_type = sys.argv[3]

plt.plot(x, y, label='')

plt.xlabel('N')
plt.ylabel('Error')
plt.title('Error plot for ' + interpolation_type + ' ' + node_type)

plt.legend()
plt.show()