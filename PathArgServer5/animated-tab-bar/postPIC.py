

import requests
from io import BytesIO
import base64
import os
from PIL import Image
import requests
import base64


import sys
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
            new_width = 240  # 等比例缩放后的图像高度，根据实际需要调整
            # print(width, " ", height)
            if width<height:
                if width > new_width:
                    ratio = round(new_width / width, 3)  # 缩放系数
                    new_im = new_im.resize((int(width * ratio)+1, int(height * ratio)+1), Image.ANTIALIAS)
                    print("new size w,h",int(width * ratio), int(height * ratio))
            else:
                if height > new_width:
                    ratio = round(new_width / height, 3)  # 缩放系数
                    new_im = new_im.resize((int(width * ratio)+1, int(height * ratio)+1), Image.ANTIALIAS)
                    print("new size w,h",int(width * ratio), int(height * ratio))
                 
            
        # 获取图像字节流，转16进制格式
        img_byte = BytesIO()  # 获取字节流
        print(img_byte)
        new_im.save(img_byte, format='jpeg')
        print("============================")
        #print(img_byte.getvalue())
        print("============================")
    return img_byte.getvalue()


def postpic_fun(pic_name):
        print("start")
        #img = cv2.imread(resize_pic_dir+pic_name)
    
        name = pic_name

        img_data = processImage(name,resaize = True)
        #print(img_data)
        
        # 将字节流转换为Base64编码的字符串
        #print(img_data)


        img_str = base64.b64encode(img_data)
        print(img_str)
        data = {'image': img_str}
        # 构造POST请求，发送图片字符串到ESP32的IP地址
        try :
            url = 'http://192.168.43.153/upload_image'
            response = requests.post(url, data=data)
                    # 输出ESP32的响应信息
            print(response.text)
            return img_str
        except requests.exceptions.ConnectionError:

        # 输出ESP32的响应信息
            #print(response.text)
            
            return img_str
  
if __name__ =="__main__":
    pic_name  = "uploaded_image.jpg"
    postpic_fun(pic_name)