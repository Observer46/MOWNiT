import matplotlib.pyplot as plt
import numpy as np

x, y = np.loadtxt('relativeErrors.txt', delimiter=' ', unpack=True)

plt.plot(x, y, label='')

plt.xlabel('Indeks tablicy')
plt.ylabel('Błąd względny')
plt.title('Błąd względny w trakcie sumowania')
plt.legend()
plt.show()