import requests
# Flask服务器的URL
url = 'http://192.168.43.185:5000/upload'

file_path = "hello.wav"
# 创建一个multipart/form-data格式的请求
files = {'file': open(file_path, 'rb')}

# 发送POST请求
response = requests.post(url, files=files)
print(response.headers)

# 检查响应
if response.status_code == 200:
    print('文件上传成功！')
else:
    print('文件上传失败！')