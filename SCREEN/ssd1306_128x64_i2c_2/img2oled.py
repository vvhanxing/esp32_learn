import cv2
import numpy as np
from matplotlib import pyplot as plt

im = cv2.imread('1.jpg', cv2.IMREAD_COLOR)
print(im.shape)
rows, cols, _ = im.shape
b = np.zeros((rows, cols), dtype=np.uint32)
g = np.zeros((rows, cols), dtype=np.uint32)
r = np.zeros((rows, cols), dtype=np.uint32)
imgout = np.zeros((rows, cols), dtype=np.uint32)

for i in range(0, rows):
    for j in range(0, cols):
        b[i, j] = im[i, j, 0]
        g[i, j] = im[i, j, 1]
        r[i, j] = im[i, j, 2]


for i in range(0, rows):
    for j in range(0, cols):
        red = np.right_shift(r[i, j], 3)
        red = np.left_shift(red, 11)
        green = np.right_shift(g[i, j], 2)
        green = np.left_shift(green, 5)
        blue = np.right_shift(b[i, j], 3)
        imgout[i, j] = red + green + blue
f = open("file2.txt", "w")
for i in range(0, rows):
    for j in range(0, cols):
        f.write(hex(imgout[i, j]) + ',')
f.close()