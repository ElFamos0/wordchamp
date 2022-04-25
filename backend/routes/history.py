from models.game_normal import Game_normal
from setup import *
from flask import request, jsonify
from utils import estGagnee

@app.route('/history', methods=['GET'])
def history():
    current_user = ""
    entries = []
    requete = Game_normal.query.filter_by(id_user=current_user).all()
    for game in requete:
        temp={"id":"", "guesses":[], "solution":"", "result":""}
        guesses=[]
        temp.id = game.id
        temp.guesses = guesses
        temp.solution = game.solution
        temp.result = estGagnee(guesses, game.solution)
        entries.append(temp)
    # return 'test'
    # à récup dans le DB plutôt que de l'écrire en dur
    return jsonify({
        "entries":[
            {"id":"10", "guesses":[{"id":"1", "word":"TESTER"}, {"id":"2", "word":"ZEROOS"}], "solution":"Oulala", "result":"Victoire", "maxtry":"3"},
            {"id":"2", "guesses":[{"id":"1", "word":"TESTS"}, {"id":"2", "word":"ZIZIS"}, {"id":"3", "word":"PIPIS"}], "solution":"Sauce", "result":"Défaite", "maxtry":"3"},
            {"id":"1", "guesses":[{"id":"1", "word":"YOOOOOOOOO"}], "solution":"sérieuxmec", "result":"NULMDR", "maxtry":"2"},
            {"id":"0", "guesses":[], "solution":"sheeeeeeeeeeeeeeeeeeesh", "result":"Défiak", "maxtry":"3"},
        ]
    })