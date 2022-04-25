from models.game_normal import Game_normal
from models.game import Game
from models.user import User
from setup import *
from flask import request, jsonify
from utils import estGagnee
from flask_jwt_extended import jwt_required, get_jwt_identity


@app.route('/history', methods=['GET'])
@jwt_required()
def history():
    utilisateur = User.query.first()
    userId=utilisateur.id
    games = Game_normal.query.filter_by(id_user=userId).all()






    identity = get_jwt_identity()
    # user = User.query.get(identity)
    # if user == None: return jsonify({"error": "user not found"}), 400
    entries = []
    # requete = Game.query.filter_by(username='pseudo').all()
    # for game in requete:
    #     temp={"id":"", "guesses":[], "solution":"", "result":""}
    #     guesses=[]
    #     temp.id = game.id
    #     temp.guesses = guesses
    #     temp.solution = game.solution
    #     temp.result = estGagnee(guesses, game.solution)
    #     entries.append(temp)
    # return requete
    # à récup dans le DB plutôt que de l'écrire en dur
    return jsonify({
        "entries":[
            {"id":"10", "guesses":[{"id":"1", "word":"TESTER"}, {"id":"2", "word":"ZEROOS"}], "solution":"Oulala", "result":"Victoire", "maxtry":"3"},
            {"id":"2", "guesses":[{"id":"1", "word":"TESTS"}, {"id":"2", "word":"ZIZIS"}, {"id":"3", "word":"PIPIS"}], "solution":"Sauce", "result":"Défaite", "maxtry":"3"},
            {"id":"1", "guesses":[{"id":"1", "word":"YOOOOOOOOO"}], "solution":"sérieuxmec", "result":"NULMDR", "maxtry":"2"},
            {"id":"0", "guesses":[], "solution":"sheeeeeeeeeeeeeeeeeeesh", "result":"Défiak", "maxtry":"3"},
        ]
    })