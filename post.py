import requests
dic = {
"info":
"""
123
"""
}
r = requests.post("http://192.168.43.192/getinfo",data=dic)
print(r.text)