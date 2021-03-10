#!/usr/bin/env python3

import sys
import matplotlib.pyplot as plt 
from itertools import cycle

colors = ['g','c', 'r', 'b', 'm', 'y', 'k']

y_array = []
x_array = []

if(len(sys.argv) != 2 + int(sys.argv[1])):
    print("Not correct amount of arguments")
    exit(0)


for i in range(2,int(sys.argv[1]) + 2):
    x_values = []
    y_values = []
    with open(sys.argv[i], "r") as file1:
         f_list = [float(i) for line in file1 for i in line.split(',') if i.strip()]

    for index, element in enumerate(f_list):
        if index % 2 == 0:
            x_values.append(int(element))
        else:
            y_values.append(element)
    x_array.append(x_values)
    y_array.append(y_values)
    plt.plot(x_array[i-2],y_array[i-2],c=colors[i%len(colors)],label=sys.argv[i])  
    

# ./grapher 3 input.txt input2.txt input3.txt

#print(x_values)
#print(y_values)

#mmult_results.txt 
#mmult_simd_results.txt 
# function to show the plot 
plt.legend()
plt.savefig('graph.png')
plt.show()
file1.close()
