from setup import *
from flask import jsonify
from utils.getword import getrandomword, getrandomwordbysize

@app.route('/word', methods=['GET'])
def wordrandom():
    # get the word from the database
    word = getrandomword()
    # return the word as a json object
    return(jsonify(word))


@app.route('/word/<id>', methods=['GET'])
def wordbysize(id):
    word = getrandomwordbysize(id)
    return(jsonify(word))