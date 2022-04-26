from models.tries import Tries
from models.game_normal import Game_normal
from models.game import Game
from models.user import User
from setup import *
from flask import request, jsonify
from utils.estGagnee import estGagnee


@app.route('/historyDebug', methods=['GET'])
def historyDebug():
    utilisateur = User.query.first()
    userId=utilisateur.id
    reqGames = Game_normal.query.filter_by(id_user=userId, state=True).order_by(Game.date.desc()).all()
    games = [e.toDict(1,1,1,1,1,1) for e in reqGames]
    entries = [{"id":e["id"], "guesses":[], "solution":e["solution"], "result":"", "maxtry":str(e["maxtry"])} for e in games]
    for entry in entries:
        reqTries = Tries.query.filter_by(id_game=entry["id"]).all()
        tries = [e.toDict(1,1,1,1) for e in reqTries]
        guesses = [{"id":e["try_number"],"word":e["word"]} for e in tries]
        entry["guesses"]=guesses
        entry["result"]= "Victoire" if estGagnee(entry) else "Défaite"
    entries = {"entries":entries}
    return jsonify(entries)
    return jsonify({
        "entries":[
            {"id":"10", "guesses":[{"id":"1", "word":"TESTER"}, {"id":"2", "word":"ZEROOS"}], "solution":"Oulala", "result":"Victoire", "maxtry":"3"},
            {"id":"2", "guesses":[{"id":"1", "word":"TESTS"}, {"id":"2", "word":"ZIZIS"}, {"id":"3", "word":"PIPIS"}], "solution":"Sauce", "result":"Défaite", "maxtry":"3"},
            {"id":"1", "guesses":[{"id":"1", "word":"YOOOOOOOOO"}], "solution":"sérieuxmec", "result":"NULMDR", "maxtry":"2"},
            {"id":"0", "guesses":[], "solution":"sheeeeeeeeeeeeeeeeeeesh", "result":"Défiak", "maxtry":"3"},
        ]
    })