from moviepy.editor import VideoFileClip
from PIL import Image
clip1 = VideoFileClip('g2.mp4')
i = 1
for frame in clip1.iter_frames():
    if i%1==0:
        im = Image.fromarray(frame)
        im.save("./frame_image/your_file_%07d.jpg" % i)
    i = i+1


# -*- coding: utf-8 -*-
"""
@File    : 200113_等比例调整图像分辨率大小.py
@Time    : 2020/1/13 13:38
@Author  : Dontla
@Email   : sxana@qq.com
@Software: PyCharm
"""
import cv2
import os

def img_resize(image):
    height, width = image.shape[0], image.shape[1]
    # 设置新的图片分辨率框架
    width_new = 240
    height_new = 240
    # 判断图片的长宽比率
    if width / height >= width_new / height_new:
        img_new = cv2.resize(image, (width_new, int(height * width_new / width)))
    else:
        img_new = cv2.resize(image, (int(width * height_new / height), height_new))
    return img_new

pic_dir = "./frame_image/"
resize_pic_dir = "./pics_resize/"
for pic_name in os.listdir(pic_dir):




    img = cv2.imread(pic_dir+pic_name)
    img_new = img_resize(img)
    print(img_new.shape)
    # cv2.imshow('win', img_new)
    # cv2.waitKey(0)
    filename="0001.jpg"
    cv2.imwrite(resize_pic_dir+pic_name, img_new)

