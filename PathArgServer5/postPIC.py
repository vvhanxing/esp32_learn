import requests
# dic = {
# "info":
# """ChatGPT4 is great,I love openAI !"""
# }
import sys
data = {
"click_once_count":
"4"
}

for i in range(1):
    url = 'http://192.168.43.247/info'
    headers = {"Content-Type": "application/json"}
    #dic["info"]=  " "*i+"""ChatGPT4 is great,I love openAI !"""
    response = requests.post(url, json=data,headers= headers)
    print(response)
    #print(response.headers)
    print(response.request.headers)

# url  ='http://192.168.43.247/showinfo'
# response = requests.get(url)
# print(response.json())

# for i in range(1):
#     r = requests.get("http://192.168.43.247/getinfo")
#     print(r.status_code)
#     print(r.text)

# encoding:utf-8
import matplotlib.pyplot as plt
#import cv2
from io import BytesIO
import base64


def processImage(in_file, saveImg=True,resaize = False):
    try:
        if "gif"  in in_file:
            im = Image.open(in_file)
        else:
            im = Image.open(in_file)

    except IOError:
        print("Cant load", in_file)
        sys.exit(1)

    # 截取文件名
    filename = in_file.split('.')[0]

    i = 0
    #if "gif"  in in_file:
        #mypalette = im.getpalette()

    arr_name_all = ''  # 存取数组
    arr_size_all = ''  # 存储数组容量


    with open(filename + '.h', 'w', encoding='utf-8') as f:  # 写入文件
        f.write('#include <pgmspace.h> \n\n')
  
        print('.', end="")
        #if "gif"  in in_file:
            #im.putpalette(mypalette)
        new_im = Image.new("RGB", im.size)
        new_im.paste(im)

        # 缩放图像，
        if resaize:
            width = new_im.size[0]  # 获取原始图像宽度
            height = new_im.size[1]  # 获取原始图像高度
            new_width = 10  # 等比例缩放后的图像高度，根据实际需要调整
            # print(width, " ", height)
            if width > new_width:
                ratio = round(new_width / width, 3)  # 缩放系数
                new_im = new_im.resize((int(width * ratio)+1, int(height * ratio)+1), Image.ANTIALIAS)
                print("new size w,h",int(width * ratio), int(height * ratio))
            
        # 获取图像字节流，转16进制格式
        img_byte = BytesIO()  # 获取字节流
        new_im.save(img_byte, format='jpeg')
        print("============================")
        print(img_byte.getvalue())
        print("============================")
    return img_byte.getvalue()


import os
#input()
from PIL import Image
import requests
import base64
# for i in range(1):
#     # 打开图片文件，读取为字节流
#     # with open('small.jpg', 'rb') as f:
#     #     img_data = f.read()
#     #     print(img_data)
#     img_data = processImage('small.jpg')
    
#     # 将字节流转换为Base64编码的字符串
#     img_str = base64.b64encode(img_data)
#     print(len(img_str))
#     # 构造POST请求，发送图片字符串到ESP32的IP地址
#     url = 'http://192.168.43.247/upload_image2'
#     img_str = """/9j/4AAQSkZJRgABAQEBLAEsAAD"""
#     data = {'image': img_str}
#     print(">>>>>>>>>data#")
#     print(data)
#     HEADERS = {'user-agent': 'application/json'}
#     response = requests.post(url,headers= HEADERS,data=data)


#     # 输出ESP32的响应信息
#     print(response.text)
# input()
resize_pic_dir = "./pics_resize/"
for pic_name in os.listdir(resize_pic_dir):




    #img = cv2.imread(resize_pic_dir+pic_name)
 
    name = resize_pic_dir+pic_name
    # 打开图片文件，读取为字节流
    # with open('small.jpg', 'rb') as f:
    #     img_data = f.read()
    #     print(img_data)
    img_data = processImage(name)
    
    # 将字节流转换为Base64编码的字符串
    print(img_data)
    print("--------------------")
    img_str = base64.b64encode(img_data)
    data = {'image': img_str}
    print(data)
    print(len(img_str))
    # 构造POST请求，发送图片字符串到ESP32的IP地址
    url = 'http://192.168.43.247/upload_image'

    response = requests.post(url, data=data)

    # 输出ESP32的响应信息
    print(response.text)    
    break