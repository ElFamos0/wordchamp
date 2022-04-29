from models.tries import Tries
from models.game_normal import Game_normal
from models.game_carriere import Game_carriere
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
    all_games_poly = with_polymorphic(game.Game, [game_normal.Game_normal, game_carriere.Game_carriere])
    reqGames = db.session.query(all_games_poly).filter_by(state = True).order_by(Game.date.desc()).all()
    games = [e.toDict(1,1,1,1,1,1,1) if e.game_type=="game_normal" else e.toDict(1,1,0,1,1,1,1,0,0,0,1) for e in reqGames]
    gamesUser = []
    for e in games:
        if e["id_user"] == userId:
            gamesUser.append(e)
    entries = [{"id":e["id"], "guesses":[], "solution":e["solution"], "result":"", "maxtry":str(e["maxtry"]), "date":e["date"], "type":e["game_type"]} for e in gamesUser]
    for entry in entries:
        reqTries = Tries.query.filter_by(id_game=entry["id"]).all()
        tries = [e.toDict(1,1,1,1) for e in reqTries]
        guesses = [{"id":e["try_number"],"word":e["word"]} for e in tries]
        entry["guesses"] = guesses
        entry["result"] = "Victoire" if estGagnee(entry) else "Défaite"
        
        #entry["colors"] = []
        #entry["date"] = datetime.datetime.fromtimestamp(1651133760108 / 1000.0, tz=datetime.timezone.utc)
    entries = {"entries":entries}
    return jsonify(entries)
    
    # return jsonify({
    #     "entries":[
    #         {"id":"10", "guesses":[{"id":"1", "word":"TESTER"}, {"id":"2", "word":"ZEROOS"}], "solution":"Oulala", "result":"Victoire", "maxtry":"3"},
    #         {"id":"2", "guesses":[{"id":"1", "word":"TESTS"}, {"id":"2", "word":"ZIZIS"}, {"id":"3", "word":"PIPIS"}], "solution":"Sauce", "result":"Défaite", "maxtry":"3"},
    #         {"id":"1", "guesses":[{"id":"1", "word":"YOOOOOOOOO"}], "solution":"sérieuxmec", "result":"NULMDR", "maxtry":"2"},
    #         {"id":"0", "guesses":[], "solution":"sheeeeeeeeeeeeeeeeeeesh", "result":"Défiak", "maxtry":"3"},
    #     ]
    # })