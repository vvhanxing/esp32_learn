from flask import Flask, render_template,jsonify
from flask import request






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


# app = Flask(
#     __name__,
#     template_folder=".",
#     static_folder=".",
#     static_url_path=""
# )



data = {
        "info":"""  Everyone is a genius. But if you judge a fish by its ability to climb a tree, it will live its whole life believing that it is stupid.
        """,
        "fontSize":4
    }


@app.route('/', methods=['GET', 'POST'])
def home():
    # html_txt='Hello'
    # #with open("index_shadow3.html","r") as  txt:
    # with open("index.html","r") as  txt:
    #     html_txt = ""
    #     html = list(txt.readlines())
    #     html_txt = "".join(html)

   return render_template("index.html")

@app.route('/neo', methods=['GET', 'POST'])
def neo_test():
    #j = request.get_json()
    #print(j["inputTxt"][0])
    print(request.get_json())
    data["info"] = request.get_json()["inputTxt"][0]
    return """ {"info": "我喜欢你" } """



@app.route('/index', methods=['GET', 'POST'])
def index():
    # 返回json数据的方法
    print("------------------")
    print(data)
    # 第二种 jsonify帮助转为json数据，并设置响应头 Content-Type 为 application/json
    return jsonify(data)






# @app.route('/signin', methods=['GET'])
# def signin_form():
#     return '''<form action="/signin" method="post">
#               <p><input name="username"></p>
#               <p><input name="password" type="password"></p>
#               <p><button type="submit">Sign In</button></p>
#               </form>'''





# @app.route('/signin', methods=['POST'])
# def signin():
#     # 需要从request对象读取表单内容：
#     if request.form['username']=='1' and request.form['password']=='1':
#         return '<h3>Hello, admin!</h3>'
#     return '<h3>Bad username or password.</h3>'



if __name__ == '__main__':
    app.run(debug=False,host=IP,port=5000) #,ssl_context="adhoc" 8000
#debug=False,host='192.168.1.111',port=5000 192.168.9.106
    #ipconfig 192.168.1.111 127.0.9.1
