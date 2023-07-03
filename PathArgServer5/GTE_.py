import requests
# Flask服务器的URL
url = 'https://semantickernalapi.azurewebsites.net/Chat'
data = {
  "content": "What'\''s new equation?"
}
headers = {"Content-Type": "application/json"}
#dic["info"]=  " "*i+"""ChatGPT4 is great,I love openAI !"""
response = requests.post(url, json=data,headers= headers)
print(response.json())
print(response)