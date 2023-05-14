# import requests
# dic = {
# "info":
# """
# 123
# """
# }
# for i in range(10):
#     r = requests.get("http://192.168.43.91/inline")
#     print(r.status_code)
#     print(r.text)




import requests
import base64
# 打开图片文件，读取为字节流
with open('small.png', 'rb') as f:
    img_data = f.read()

# 将字节流转换为Base64编码的字符串
img_str = base64.b64encode(img_data).decode('utf-8')

# 构造POST请求，发送图片字符串到ESP32的IP地址
url = 'http://192.168.43.247/upload_image'
data = {'image': img_str}
response = requests.post(url, data=data)

# 输出ESP32的响应信息
print(response.text)
