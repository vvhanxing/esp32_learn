from flask import Flask, request, jsonify
from flask import request,render_template,url_for
app = Flask(__name__)


@app.route('/', methods=['GET','POST'])
def index():
    return render_template("index.html")

@app.route('/upload', methods=['POST'])
def upload():
    data = request.get_json()
    resized_base64 = data.get('image')
    print(resized_base64)
    # Handle the resized_base64 as needed (e.g., save it to a file, process it further, etc.)
    # For simplicity, let's just return the received data as JSON
    return jsonify({'message': 'Image received successfully'})

if __name__ == '__main__':
    app.run(debug=True)
