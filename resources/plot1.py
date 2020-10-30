import matplotlib.pyplot as plt
x1 = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12]
y1 = [132.388, 133.095, 66.71, 44.808, 33.836, 27.154, 22.819, 19.566, 17.556, 15.663, 14.249, 12.937]
z1 = []

for i in range(0, 12):
    print(i)
    z1.append(132.388/y1[i])
# plt.plot(x1,z1)
# plt.show()

results = [[2, 134.4], [3, 67.329],[4,44.858],[5,33.867],[6,27.284],[7, 22.973], [8, 20.05], [9,17.628], [10, 15.595], [11, 14.177], [12, 13.021], [13, 11.814],[14, 10.802],[15,10.526], [16,  9.559],[17, 9.274], [18 ,9.763 ], [19 , 8.116], [20 , 7.899],[21 , 7.687], [22 , 6.957], [23 , 6.834], [24 , 6.753], [25 , 6.512], [26 ,6.207], [27 , 5.818], [28 , 5.636], [29 , 5.592], [30 , 5.501], [31, 5.497], [32, 5.427]]
# x = []
# z = []
# for result in results:
#     print(result)
#     x.append(result[0])
#     z.append(result[1]*(result[0]-1))
# plt.plot(x,z)
# plt.show()
x = []
z = []
for result in results:
    print(result)
    x.append(result[0])
    z.append(132.388/result[1])
plt.plot(x,z)
# plt.plot(x1,z1)
plt.xlabel("Number of cores")
plt.ylabel("Speedup")
plt.show()