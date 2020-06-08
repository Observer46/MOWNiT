import matplotlib.pyplot as plt
import numpy as np
import sys


print("argv[]: 1 -> input|freq|fourier, 2 -> fourier_res1.txt, 3 -> fourier_res2.txt, 4 -> data_name1, 5 -> data_name2")
mode = sys.argv[1]
if mode == "input":
    print("data - parsed_data.txt")
    data_name = "parsed_data.txt"
    plot_name = "Humidity data for 8 days of May 2020 in Vancouver"

    data_x, data_y = np.loadtxt(data_name, delimiter=' ', unpack=True)
    plt.plot(data_x, data_y, label='Humidity', color = 'c')

    plt.xlabel('Day of May')
    plt.ylabel('Humidity [%]')
elif mode == "freq":
    print("freq - freq_data.txt")
    data_name = "freq_data.txt"
    plot_name = "Spectrum of humidity change"

    data_x, data_y = np.loadtxt(data_name, delimiter=' ', unpack=True)
    plt.scatter(data_x, data_y, label='Transform value', color = 'r')

    idx = 0
    
    data_y1 = [float(x) for x in data_y]
    maxi = float(0)
    for i in range(1, len(data_y1)):
        if data_y1[i] > maxi:
            maxi = data_y1[i]
            idx = i

    plt.scatter(data_x[idx], data_y[idx], label='Max value', color = 'g')
    plt.text(data_x[idx], data_y[idx], '({}, {})'.format(data_x[idx], data_y[idx]))

    plt.xlabel('Frequency in change cycles/hour [1/h]')
    plt.ylabel('Humidity frequency spectrum magnitude')
    plt.ylim(-1,2000)
elif mode == "fourier":
    fourier_file1 = sys.argv[2]
    fourier_file2 = sys.argv[3]
    data_name1 = sys.argv[4]
    data_name2 = sys.argv[5]
    plot_name = "Time comparison: " + data_name1 + " and " + data_name2 

    data1_x, data1_y = np.loadtxt(fourier_file1, delimiter=' ', unpack=True)
    data2_x, data2_y, _, _ = np.loadtxt(fourier_file2, delimiter=' ', unpack=True)

    plt.plot(data1_x, data1_y, label=data_name1, color = 'r')
    plt.plot(data2_x, data2_y, label=data_name2, color = 'b')
    plt.xlabel('Input size')
    plt.ylabel('Time [microseconds]')

else:
    print("Unknown plot mode")
    exit(1)

plt.title(plot_name)
plt.legend()
plt.show()