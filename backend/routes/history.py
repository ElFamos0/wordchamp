from setup import *
from flask import request, jsonify

@app.route('/history', methods=['GET'])
def history():
    # à récup dans le DB plutôt que de l'écrire en dur
    return jsonify({
        "entries":[
            {"id":"1", "motFinal":"Oulala", "result":"Victoire"},
            {"id":"2", "motFinal":"MaitreSauceur", "result":"Défaite"},
            {"id":"3", "motFinal":"sérieuxmec", "result":"NULMDR"},
            {"id":"4", "motFinal":"sheeeeeeeeeeeeeeeeeeesh", "result":"Défiak"},
        ]
        })