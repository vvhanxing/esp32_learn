import requests
dic = {
"info":
"""
123
"""
}
for i in range(10):
    r = requests.get("http://192.168.43.91/inline")
    print(r.status_code)
    print(r.text)