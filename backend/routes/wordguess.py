from setup import *
from flask import jsonify


@app.route('/wordguess/<string:guess>/<string:solution>', methods=['GET'])
def wordguess():
    print("wordguess")
    return jsonify("wordguess")