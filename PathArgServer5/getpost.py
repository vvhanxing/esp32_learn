import requests
# dic = {
# "info":
# """ChatGPT4 is great,I love openAI !"""
# }

data = {
"click_once_count":
"4"
}

for i in range(1):
    url = 'http://127.0.0.1:5000/info'
    headers = {"Content-Type": "application/json"}
    #dic["info"]=  " "*i+"""ChatGPT4 is great,I love openAI !"""
    response = requests.post(url, json=data,headers= headers)
    print(response)
    #print(response.headers)
    print(response.request.headers)

url  ='http://127.0.0.1:5000/showinfo'
response = requests.get(url)
print(response.json())

# for i in range(1):
#     r = requests.get("http://192.168.43.247/getinfo")
#     print(r.status_code)
#     print(r.text)




input()
import requests
import base64
# 打开图片文件，读取为字节流
with open('a2.jpg', 'rb') as f:
    img_data = f.read()

# 将字节流转换为Base64编码的字符串
img_str = base64.b64encode(img_data).decode('utf-8')

# 构造POST请求，发送图片字符串到ESP32的IP地址
url = 'http://192.168.43.247/upload_image'
data = {'image': img_str}
response = requests.post(url, data=data)

# 输出ESP32的响应信息
print(response.text)


#picture encoding base64 string post to esp32 webserver,
#arduino esp32 use webserver to get base64 string ,decoded base64 string and use TFT_eSPI to show picture in tft lcd 