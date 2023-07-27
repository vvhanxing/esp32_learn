from flask import Flask, send_file, Response, send_from_directory
from flask import jsonify,request,render_template,url_for


app = Flask(__name__)


@app.route("/",methods = ["GET","POST"])
def chat():

    return render_template("webgl_loader_obj_mtl.html")




if __name__ == '__main__':
    app.run(host="localhost",port=5000 ,debug=True)




