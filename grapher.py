#!/usr/bin/env python3

import sys
import matplotlib.pyplot as plt 
x_values = []
y_values = []

with open("mmult_simd_results.txt", "r") as file1:
    f_list = [float(i) for line in file1 for i in line.split(',') if i.strip()]

for index, element in enumerate(f_list):
    if index % 2 == 0:
        y_values.append(int(element))
    else:
        x_values.append(element)



print(x_values)
print(y_values)

plt.plot(x_values,y_values)   
# function to show the plot 
plt.show()

file1.close()
