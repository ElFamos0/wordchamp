from setup import *
from flask import request, jsonify

@app.route('/history', methods=['GET'])
def history():
    # à récup dans le DB plutôt que de l'écrire en dur
    return jsonify({
        "entries":[
            {"id":"1", "guesses":[{"id":"1", "word":"test"}, {"id":"2", "word":"zero"}], "solution":"Oulala", "result":"Victoire"},
            {"id":"2", "guesses":[{"id":"1", "word":"test"}, {"id":"2", "word":"zizi"}, {"id":"3", "word":"pipi"}], "solution":"MaitreSauceur", "result":"Défaite"},
            {"id":"3", "guesses":[{"id":"1", "word":"yooo"}], "solution":"sérieuxmec", "result":"NULMDR"},
            {"id":"4", "guesses":[], "solution":"sheeeeeeeeeeeeeeeeeeesh", "result":"Défiak"},
        ]
        })