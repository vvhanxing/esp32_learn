from flask import Flask, send_file, Response, send_from_directory
from flask import jsonify,request,render_template
import io
import re
import json

J ={}
app = Flask(__name__)

@app.route("/",methods = ["GET","POST"])
def chat():

    return render_template("index.html")

@app.route("/info",methods = ["GET","POST"])
def info():
    global J
    J = request.get_json()
    return J

@app.route("/showinfo",methods = ["GET","POST"])
def showinfo():
    
    return json.dumps(J)

if __name__ == '__main__':
    app.run(debug=True)

