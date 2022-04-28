from models.tries import Tries
from models.game_normal import Game_normal
from models.game import Game
from setup import *
from flask import request, jsonify
from utils.estGagnee import estGagnee
from flask_jwt_extended import jwt_required, get_jwt_identity
from utils.wordcheck import check_word
import datetime


@app.route('/history', methods=['GET'])
@jwt_required()
def history():
    identity = get_jwt_identity()
    userId = identity
    reqGames = Game_normal.query.filter_by(id_user=userId, state=1).order_by(Game.date.desc()).all()
    games = [e.toDict(1,1,1,1,1,1) for e in reqGames]
    entries = [{"id":e["id"], "guesses":[], "solution":e["solution"], "result":"", "maxtry":str(e["maxtry"]), "date":e["date"]} for e in games]
    for entry in entries:
        reqTries = Tries.query.filter_by(id_game=entry["id"]).all()
        tries = [e.toDict(1,1,1,1) for e in reqTries]
        guesses = [{"id":e["try_number"],"word":e["word"]} for e in tries]
        entry["guesses"] = guesses
        entry["result"] = "Victoire" if estGagnee(entry) else "Défaite"
        entry["colors"] = []
        for guess in guesses:
            entry["colors"].append(check_word(guess["word"], entry["solution"]))
        #entry["date"] = datetime.datetime.fromtimestamp(1651133760108 / 1000.0, tz=datetime.timezone.utc)
    entries = {"entries":entries}
    print(entries)
    return jsonify(entries)
    
    # return jsonify({
    #     "entries":[
    #         {"id":"10", "guesses":[{"id":"1", "word":"TESTER"}, {"id":"2", "word":"ZEROOS"}], "solution":"Oulala", "result":"Victoire", "maxtry":"3"},
    #         {"id":"2", "guesses":[{"id":"1", "word":"TESTS"}, {"id":"2", "word":"ZIZIS"}, {"id":"3", "word":"PIPIS"}], "solution":"Sauce", "result":"Défaite", "maxtry":"3"},
    #         {"id":"1", "guesses":[{"id":"1", "word":"YOOOOOOOOO"}], "solution":"sérieuxmec", "result":"NULMDR", "maxtry":"2"},
    #         {"id":"0", "guesses":[], "solution":"sheeeeeeeeeeeeeeeeeeesh", "result":"Défiak", "maxtry":"3"},
    #     ]
    # })