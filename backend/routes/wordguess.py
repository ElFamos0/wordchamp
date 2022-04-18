from setup import *
from flask import jsonify, request
from models.word import Word


@app.route('/guess', methods=['POST'])
def guess():
    id = request.json["id"]
    guess = request.json["guess"]
    # get the word from the database
    word = Word.query.get(id)
    if len(word.word) != len(guess):
        return jsonify({"error": "wrong length"}), 400
    array = []
    for i in range(len(guess)):
        if guess[i] == word.word[i]:
            array.append("right")
        elif guess[i] in word.word:
            amount = word.word[i:].count(guess[i])
            array.append(amount)
        else:
            array.append("wrong")
    # returns an encoded description of the guess
    return jsonify(array), 200