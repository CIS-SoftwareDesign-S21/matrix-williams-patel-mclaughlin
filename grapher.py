#!/usr/bin/env python3

import matplotlib.pyplot as plt 
x_values = []
y_values = []
file1 = open('myfile.txt', 'r')
Lines = file1.readlines()
count = 1
for line in Lines:
    x_values.append(line.strip('\n'))
    y_values.append('n'+str(count))
    count += 1
print(x_values)
print(y_values)

plt.plot(x_values,y_values) 
  
# function to show the plot 
plt.show()