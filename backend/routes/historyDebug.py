from models.game_normal import Game_normal
from models.game import Game
from models.user import User
from setup import *
from flask import request, jsonify
from utils import estGagnee


@app.route('/historyDebug', methods=['GET'])
def historyDebug():
    utilisateur = User.query.first()
    return utilisateur.toDict()
    return jsonify({
        "entries":[
            {"id":"10", "guesses":[{"id":"1", "word":"TESTER"}, {"id":"2", "word":"ZEROOS"}], "solution":"Oulala", "result":"Victoire", "maxtry":"3"},
            {"id":"2", "guesses":[{"id":"1", "word":"TESTS"}, {"id":"2", "word":"ZIZIS"}, {"id":"3", "word":"PIPIS"}], "solution":"Sauce", "result":"Défaite", "maxtry":"3"},
            {"id":"1", "guesses":[{"id":"1", "word":"YOOOOOOOOO"}], "solution":"sérieuxmec", "result":"NULMDR", "maxtry":"2"},
            {"id":"0", "guesses":[], "solution":"sheeeeeeeeeeeeeeeeeeesh", "result":"Défiak", "maxtry":"3"},
        ]
    })