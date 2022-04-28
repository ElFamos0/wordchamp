from models.dictionnaire import Dictionnaire
from flask_login import current_user
from numpy import identity
from setup import *
from flask import jsonify, request
from flask_jwt_extended import jwt_required, get_jwt_identity
from models.user import User
from models.game import Game
from models.game_normal import Game_normal
from models.tries import Tries
from models.word import Word
from utils.getword import getrandomword, getrandomwordbysize
from sqlalchemy.orm import with_polymorphic
from utils.classLeters import classLeters


@app.route('/creategame/<taille>/<maxtry>', methods=['GET'])
@jwt_required()
def creategame(taille, maxtry):
    if not (9>=int(taille)>=5):
        taille = 5
    if not (10>=int(maxtry)>=1):
        maxtry = 6
    identity = get_jwt_identity()
    current_user = User.query.get(identity)
    if current_user == None: return jsonify({"error": "user not found"}), 400
    all_games_poly = with_polymorphic(game.Game, [game_normal.Game_normal, game_carriere.Game_carriere])
    all_games = db.session.query(all_games_poly).filter(all_games_poly.Game_normal.id_user == current_user.id,all_games_poly.Game_normal.state == False).all()

    data = {"solution" : "", "guess" : [], "currenttry":0, "maxtry":0, "motsValides" : [],"miss" : [],"found" : [],"misplace" : []}
    if len(all_games) == 0:
        word = getrandomwordbysize(taille)
        data["solution"] = word
        data["maxtry"] = int(maxtry)
        newGameNormal = game_normal.Game_normal(current_user.id,word,int(maxtry),len(word))       #(last attribut = date en timestamp)
        for i in range(int(maxtry)):
            data["guess"].append("")
        db.session.add(newGameNormal)
        db.session.commit()
        # print(data)
    else:
        current_game = all_games[0]
        data["maxtry"] = current_game.maxtry 
        print(current_game)
        data["solution"] = current_game.solution
        guess = db.session.query(tries.Tries).filter_by(id_game = current_game.id).order_by(tries.Tries.try_number).all()

        for elm in guess:
            data["guess"].append(elm.word)
        for i in range(current_game.maxtry - len(guess)):
            data["guess"].append("")   
        data["currenttry"] = len(guess)
        # print(data)

        data["miss"],data['found'],data['misplace'] = classLeters(data["guess"],data['solution'])


    data["motsValides"]=[e.word for e in db.session.query(Dictionnaire).filter_by(size = len(data["solution"]))]
        
    return jsonify(data),200
