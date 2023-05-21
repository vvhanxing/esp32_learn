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
import cv2
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



#input()
from PIL import Image
import requests
import base64
for i in range(1):
    # 打开图片文件，读取为字节流
    # with open('small.jpg', 'rb') as f:
    #     img_data = f.read()
    #     print(img_data)
    img_data = processImage('a2.jpg')
    input("------------------2")
    # 将字节流转换为Base64编码的字符串
    img_str = base64.b64encode(img_data)
    print(len(img_str))
    # 构造POST请求，发送图片字符串到ESP32的IP地址
    url = 'http://192.168.43.247/upload_image'
    data = {'image': img_str}
    response = requests.post(url, data=data)

    # 输出ESP32的响应信息
    print(response.text)


    #picture encoding base64 string post to esp32 webserver,
    #arduino esp32 use webserver to get base64 string ,decoded base64 string and use TFT_eSPI to show picture in tft lcd 
print("-------------------")




# 二进制读取图片,再将图片转为 base64 类型的字符串
with open('small.jpg', 'rb') as fin:   #第一个参数为图片全路径或相对路径
    print('二进制类型')
    image_data = fin.read()
    # 图片:二进制类型
    print(image_data)

    # 将二进制图片编码为 base64 格式
    print('二进制类型--转--bytes类型')
    base64_data_bytes = base64.b64encode(image_data)
    # 图片:bytes类型
    print(base64_data_bytes)

    # 在Python3以后，字符串和bytes类型彻底分开了。字符串是以字符为单位进行处理的，bytes类型是以字节为单位处理的。
    # 在 Python3 中，bytes和str的互相转换方式是
    # str.encode('utf-8')           bytes.decode('utf-8')

    print('bytes类型--转--str类型')
    base64_data_str= base64_data_bytes.decode()
    # 图片:str类型
    print(base64_data_str)
######################################################################
print('上面将图片转为字符串----下面再将此字符串转为图片')
print('通过打印str类型，再将其赋给一个变量，则这个变量就表示一张图片的str类型')
print('str类型表示会很长，可以用于pythonn使用PyInstalle库生成的exe文件中')
print('上面将图片转为字符串----下面再将此字符串转为图片')
######################################################################
print('str类型')
print(base64_data_str)

print('str类型--转--bytes类型')
base64_data_bytes = base64_data_str.encode('utf-8')
print(base64_data_bytes)

print('bytes类型--转--二进制类型')
image_data = base64.b64decode(base64_data_bytes)
print(image_data)

print('二进制类型--转--数组')
# 使用 matplotlib,io 库将二进制类型转为数组
img_data = plt.imread(BytesIO(image_data),"JPG")
#第一个参数目前还不清楚
# 第二个参数可以为 PNG、JPG
print(type(img_data))
print(img_data.shape)

# 使用cv2库显示图片
img_cv2 = cv2.cvtColor(img_data,cv2.COLOR_RGB2BGR)
cv2.imshow('a',img_cv2)
cv2.waitKey(0)
cv2.destroyAllWindows()