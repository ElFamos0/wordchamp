from setup import *
from utils.isMot import isMot
from flask import jsonify

@app.route('/motValideDebug', methods=['GET'])
def motValideDebug():
    reqAllWords =  word.Word.query.all()
    allWords = [e.toDict(0, 1, 0)["word"] for e in reqAllWords]
    return jsonify(allWords)