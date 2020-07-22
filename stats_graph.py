import matplotlib.pyplot as plt 
import os
if os.stat("study_logs.txt").st_size == 0:
        print("study_logs.txt is empty.\nNo data to plot on.")
else:
        f = open("study_logs.txt", "r")
        i = 1
        j = 1
        k = 3
        x = []
        y = []
        for lines in f:
                if i == j:
                        j += 4
                        parts = lines.split()
                        x.append(int(parts[1]))
                elif i == k:
                        k += 4
                        parts = lines.split(":")
                        y.append((int(parts[1].strip()) * 60) + int(parts[2]))
                i += 1
        plt.plot(x, y, color='black', linestyle='dashed', linewidth = 3, 
                 marker='o', markerfacecolor='grey', markersize=8) 
        plt.xlabel("day number")
        plt.ylabel("time studied (in mins)")
        plt.title("study statistics")
        plt.show()
