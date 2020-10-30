import matplotlib.pyplot as plt
x = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12]
y = [132.388, 133.095, 66.71, 44.808, 33.836, 27.154, 22.819, 19.566, 17.556, 15.663, 14.249, 12.937]
z = []

for i in range(0, 12):
    print(i)
    z.append(y[i]*(x[i]-1))
plt.plot(x,z)
plt.show()