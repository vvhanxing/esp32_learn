from flask import Flask, send_file, Response, send_from_directory
from flask import jsonify,request,render_template,url_for
from flask_cors import CORS, cross_origin

import postPIC
import io
import re
import json
import wave
def save_audio_file(audio_data, output_file):
    with wave.open(output_file, 'wb') as wf:
        wf.setnchannels(1)  # 设置为单声道
        wf.setsampwidth(2)  # 16位采样宽度（每个样本2个字节）
        wf.setframerate(16000)  # 设置采样率为16000 Hz
        wf.writeframes(audio_data)


conut = 0
audio_data = b""
J ={}
app = Flask(__name__)
cors = CORS(app, resources={r"/*": {"origins": "http://192.168.43.216:5000"}})



@app.route("/index3",methods = ["GET","POST"])
def ui():

    return render_template("index4.html")

@app.route("/",methods = ["GET","POST"])
def chat():

    return render_template("index2.html")

# @app.route("ui/",methods = ["GET","POST"])
# def ui():

#     return render_template("index3.html")

@app.route("/uploadpic",methods = ["GET","POST"])
def uplodapic():
    
    return render_template("upload2.html")


@app.route("/uploadpic2",methods = ["GET","POST"])
def uplodapic2():
    
    return render_template("uploadesp32pichtml.html")

@app.route("/uploadpic5",methods = ["GET","POST"])
def uplodapic5():
    
    return render_template("upload5.html")


@app.route("/getapic",methods = ["GET","POST"])
def getapic():
    image = request.files['image']
    image.save('uploaded_image.jpg')  # 保存上传的图片，可以根据需要修改保存路径和文件名
   
    picbase64  =  postPIC.postpic_fun('uploaded_image.jpg')
    return {"picbase64":picbase64}

@app.route("/getapic2",methods = ["GET","POST"])
def getapic2():
    print( request.get_json())
  
    data = postPIC.postpic_fun('uploaded_image.jpg')
    return data

@app.route("/info",methods = ["GET","POST"])
def info():
    global J
    J = request.get_json()
    return J

@app.route("/showinfo",methods = ["GET","POST"])
def showinfo():
    
    return json.dumps(J)

@app.route('/audio', methods=['POST'])
def receive_audio():
    global conut
    global audio_data
    conut+=1
    audio_data += request.get_data()

    #print(audio_data)
    if conut%50==0:
        audio_data = audio_data  # 替换为你的音频字节流字符串
        output_file = str(conut)+'output.wav'  # 输出文件名
        print(conut)

        save_audio_file(audio_data, output_file)
        audio_data = b""

@app.route('/audio/mp3')
def stream_mp3():
    

    # def generate():
    #     path = 'C:/Users/vv/Desktop/myGithub/esp32_learn/PathArgServer5/animated-tab-bar/static/Aria.mp3'
    #     with open(path, 'rb') as fmp3:
    #         data = fmp3.read(1024)
    #         while data:
    #             yield data
    #             data = fmp3.read(1024)
    # return Response(generate(), mimetype="audio/mpeg3")
    audio_file = 'C:/Users/vv/Desktop/myGithub/esp32_learn/PathArgServer5/animated-tab-bar/static/music2.mp3'
    return send_file(audio_file, mimetype='audio/mpeg')

    

# @app.route('/audio.mp3')
# def audio():
#     # 从服务器本地文件系统读取音频文件
#     audio_file = 'C:/Users/vv/Desktop/myGithub/esp32_learn/PathArgServer5/animated-tab-bar/static/Aria.mp3'
#     return send_file(audio_file, mimetype='audio/mpeg')






    # 在这里处理音频数据，例如保存到文件或进行进一步处理

    return 'Audio received'


if __name__ == '__main__':
    app.run(host="192.168.43.185",port=5000 ,debug=True)

