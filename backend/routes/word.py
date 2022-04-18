from setup import *
from flask import jsonify
from utils.getword import getrandomword, getrandomwordbysize

@app.route('/word', methods=['GET'])
def play():
    # get the word from the database
    word = getrandomword()
    # return the word as a json object
    return jsonify({
        "id": word.id, 
        "size": word.size
    })