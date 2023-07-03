import wave
from pyaudio import PyAudio,paInt16

from flask import jsonify,request,render_template,Flask
import requests
# 设置采样参数
app = Flask(__name__)




NUM_SAMPLES = 2000
TIME = 2
chunk = 1024

# 读wav文件
def read_wave_file(filename):	
    fp = wave.open(filename,'rb')
    nf = fp.getnframes()     #获取采样点数量
    f_len = nf*2
    audio_data = fp.readframes(nf)

# 保存wav音频文件 
def save_wave_file(filename,data):  
    wf = wave.open(filename,'wb')
    wf.setnchannels(1)  
    wf.setsampwidth(2)     
    wf.setframerate(16000) 
    wf.writeframes(b"".join(data))  
    wf.close()

# 录音
def record():
    pa = PyAudio()   
    # 打开输入流并设置音频采样参数 1 channel 16K framerate 
    stream = pa.open(format = paInt16,
                     channels=1,
                     rate=16000,
                     input=True,
                     frames_per_buffer=NUM_SAMPLES)	
    audioBuffer = []   # 录音缓存数组
    count = 0	
    # 录制40s语音
    while count<TIME*20:
        string_audio_data = stream.read(NUM_SAMPLES) #一次性录音采样字节的大小
        audioBuffer.append(string_audio_data)
        count +=1
        print('.'),  #加逗号不换行输出	
    # 保存录制的语音文件到record_voice.wav中并关闭流
    save_wave_file('record_voice.wav',audioBuffer)
    pathname='record_voice.wav'
    stream.close()
    return pathname

# 播放后缀为wav的音频文件
def play(pathname):
    wf = wave.open(pathname,'rb') 
    p = PyAudio()               	
    # 打开流
    stream = p.open( format=p.get_format_from_width(wf.getsampwidth()),
                     channels=wf.getnchannels(),
                     rate=wf.getframerate(),
                     output=True)
    # 播放音频
    while True:
        data = wf.readframes(chunk)
        if data == "":break
        stream.write(data)	
    # 释放IO
    stream.stop_stream()
    stream.close()
    p.terminate()


# Flask服务器的URL
# def putvoice(file_path,url):

#     # 创建一个multipart/form-data格式的请求
#     files = {'file': open(file_path, 'rb')}

#     # 发送POST请求
#     response = requests.put(url, files=files)
#     print(response.headers)

#     # 检查响应
#     if response.status_code == 200:
#         print('文件上传成功！')
#     else:
#         print('文件上传失败！')

def send_wav_file(url, filepath):
    with open(filepath, 'rb') as f:
        files = {'file': f}
        response = requests.post(url, files=files)
    return response

@app.route("/talk",methods = ["GET","POST"])
def talk():
    print('record ready...')
    pathname=record()
    print(pathname)
    url = 'http://192.168.43.185:5000/upload'
    response = send_wav_file(url,pathname)
    print('record over!') 

    save_path = "response_voice.wav"
    with open(save_path, 'wb') as f:
        f.write(response.content)

    play(save_path)



    return "OK"

if __name__ == '__main__': 

    # print('record ready...')
    # pathname=record()
    # print(pathname)
    # url = 'http://192.168.43.185:5000/upload'
    # send_wav_file(url,pathname)
    # print('record over!') 
    # data  =request.data
    # print(data)
    # play(pathname)
    app.run(host="192.168.43.185",port=5001 ,debug=True)
