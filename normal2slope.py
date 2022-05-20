import cv2
import numpy

img = cv2.imread('anisonoiseTile_Normal.png')
rows,cols,_ = img.shape

BMap = numpy.zeros([rows, cols, 3])
MMap = numpy.zeros([rows, cols, 3])


xmin, xmax = 9999, -9999
ymin, ymax = 9999, -9999
zmin, zmax = 9999, -9999


for i in range(rows):
    for j in range(cols):
        k = img[i,j]
        x = k[2]/128.0 - 1.0
        y = k[1]/128.0 - 1.0
        z = k[0]/128.0 - 1.0

        if x < xmin: xmin = x
        if x > xmax: xmax = x
        if y < ymin: ymin = y
        if y > ymax: ymax = y
        if z < zmin: zmin = z
        if z > zmax: zmax = z

        BMap[i,j,2] = x/z
        BMap[i,j,1] = y/z
        BMap[i,j,0] = 0
        
        MMap[i,j,2] = x/z * x/z
        MMap[i,j,1] = y/z * y/z
        MMap[i,j,0] = x/z * y/z

        BMap[i,j,2] = BMap[i,j,2] * 128.0 + 128
        BMap[i,j,1] = BMap[i,j,1] * 128.0 + 128
        BMap[i,j,0] = BMap[i,j,0] * 128.0 + 128
        
        MMap[i,j,2] = MMap[i,j,2] * 128.0 + 128
        MMap[i,j,1] = MMap[i,j,1] * 128.0 + 128
        MMap[i,j,0] = MMap[i,j,0] * 128.0 + 128
        #print(f"{BMap[i, j]}   {MMap[i, j]}")

print(f"xmax:{xmax} xmin{xmin} ymax:{ymax} ymin:{ymin} zmax: {zmax} zmin:{zmin}")

cv2.imwrite("B.png", BMap)
cv2.imwrite("M.png", MMap)
