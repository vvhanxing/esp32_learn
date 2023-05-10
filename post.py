import requests
dic = {
"info":"1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16",
"num":"100"
# """
# 123 wocao
# """
}
r = requests.post("http://192.168.43.247/getinfo",data=dic)

print(r.text)