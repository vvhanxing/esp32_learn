from flask import Flask, request
import os
import wave

app = Flask(__name__)

UPLOAD_FOLDER = 'uploads'
if not os.path.exists(UPLOAD_FOLDER):
    os.makedirs(UPLOAD_FOLDER)


@app.route('/', methods=['POST'])
def hi():
    return "hi"


@app.route('/upload', methods=['POST'])
def upload_file():
    try:
        # 从请求中获取二进制数据
        audio_data = request.data

        # 将二进制数据写入.wav文件
        with wave.open('uploaded_audio.wav', 'wb') as wf:
            wf.setnchannels(1)  # 单声道
            wf.setsampwidth(2)  # 16位采样
            wf.setframerate(16000)  # 采样率为16000Hz
            wf.writeframes(audio_data)

        return  'Audio uploaded successfully'
    except Exception as e:
        return 'error'



if __name__ == '__main__':
    app.run(host='192.168.43.185', port=5000, debug=True)
