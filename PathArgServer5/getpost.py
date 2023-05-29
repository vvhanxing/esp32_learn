import requests
from io import BytesIO
import io
import base64
import requests
import json
from pydub import AudioSegment
from pydub.playback import play


def getGPT():
    url = "http://192.168.43.185:5000/openai/"

    headers = {"Content-Type":"application/json"}
    response = requests.post(url = url,headers=headers,json = {"content":["请简单介绍一下python"]})
    print(response.text)
    print(response.status_code)

if __name__ == '__main__':
    getGPT()