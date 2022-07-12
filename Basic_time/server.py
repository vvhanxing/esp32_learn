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


data = {
        "info":"""  Everyone is a genius. But if you judge a fish by its ability to climb a tree, it will live its whole life believing that it is stupid.
        """,
        "fontSize":2
    }



app = Flask(__name__)



@app.route('/', methods=['GET', 'POST'])
def home():
    return "home"


@app.route('/put_info', methods=['GET', 'POST'])
def put_info():
    
    j_data = request.get_data(as_text=True)
    print(j_data)
    # print(r_data)
    # data = r_data
    # info = request.form['info']
    # fontSize = request.form['fontSize']
    # return jsonify({"info":info,"info":fontSize })  # 
    # j_data = json.loads(j_data)
    # data = jsonify(j_data)
    return {'data': j_data}



@app.route('/index', methods=['GET', 'POST'])
def index():
    # 返回json数据的方法

    # 第二种 jsonify帮助转为json数据，并设置响应头 Content-Type 为 application/json
    return jsonify(data)

if __name__ == '__main__':
    app.run(debug = False,host=IP,port=5000)
