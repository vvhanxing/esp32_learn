from flask import Flask, render_template,jsonify
from flask import request
import json

import socket
def extract_ip():
    st = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    try:       
        st.connect(('10.255.255.255', 1))
        IP = st.getsockname()[0]
    except Exception:
        IP = '127.0.0.1'
    finally:
        st.close()
    return IP
print(extract_ip())
IP = extract_ip()






app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def view():

    return "Everyone is a genius"



@app.route('/index', methods=['GET', 'POST'])
def index():
    # 返回json数据的方法
    data = {
        "name":"Everyone is a genius. \nBut if you judge a fish by its ability to climb a tree, it will live its whole life believing that it is stupid.",
        "number":2
    }
    # 第二种 jsonify帮助转为json数据，并设置响应头 Content-Type 为 application/json
    return jsonify(data)

if __name__ == '__main__':
    app.run(debug = False,host=IP,port=5000)
