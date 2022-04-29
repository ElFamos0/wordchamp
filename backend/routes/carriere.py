from flask_login import current_user
from numpy import identity
from setup import *
from flask import jsonify, request
from flask_jwt_extended import jwt_required, get_jwt_identity
from models.user import User
from models.game import Game
from models.game_normal import Game_normal
from models.game_carriere import Game_carriere
from models.tries import Tries
from sqlalchemy.orm import with_polymorphic
from utils.classLeters import classLeters
from utils.eloFunctions import newElo


@app.route('/carriere/<ranked>', methods=['GET'])
@jwt_required()
def carriere(ranked):
    
    if ranked == "1" :
        mult = 1
    else :
        mult = 0

    identity = get_jwt_identity()
    current_user = User.query.get(identity)
    if current_user == None: return jsonify({"error": "user not found"}), 400

    all_games_poly = with_polymorphic(game.Game, [game_normal.Game_normal, game_carriere.Game_carriere])
    all_games = db.session.query(all_games_poly).filter(all_games_poly.Game_carriere.id_user == current_user.id,all_games_poly.Game_carriere.state == False).all()
    
    data = {"solution" : "", "guess" : [], "currenttry":0, "maxtry":0,"motsValides" : [],"miss" : [],"found" : [],"misplace" : [],
            "length" : 0, "elo_p" : 0, "difficulty" : 0,"ranked" : False,"elop" : 0,"elom" : 0,'n_elop':0,'n_elom':0}


    if len(all_games) == 0:
        if int(ranked) == 1 :
            
            newGameCarriere = game_carriere.Game_carriere(current_user.id,True)
        else :
            newGameCarriere = game_carriere.Game_carriere(current_user.id,False)
        data["solution"] = newGameCarriere.solution
        data["maxtry"] = newGameCarriere.maxtry
        data["length"] = newGameCarriere.length
        data["difficulty"] = round(newGameCarriere.difficulty,2)
        data["elo_player"] = round(newGameCarriere.elo_player,2)
        data["ranked"] = newGameCarriere.ranked
        data["elop"] = round(newElo(data["elo_player"],data["difficulty"],True),2) * mult
        data["elom"] = round(newElo(data["elo_player"],data["difficulty"],False),2) * mult
        data["n_elom"] = max(0,round(data["elo_player"] +  data["elom"],2))
        data["n_elop"] = max(0,round(data["elo_player"] +  data["elop"],2))
           
        maxtry = data["maxtry"]
        
        for i in range(int(maxtry)):
            data["guess"].append("")

        db.session.add(newGameCarriere)
        db.session.commit()
        #print(data)



    else:
        current_game = all_games[0]
        print(current_game.toDict(1,1,1,1,1,1,1,1,1,1))

        data["solution"] = current_game.solution
        data["maxtry"] = current_game.maxtry
        data["length"] = current_game.length
        data["difficulty"] = round(current_game.difficulty,2)
        data["elo_player"] = round(current_game.elo_player,2)
        data["ranked"] = current_game.ranked

        if data["ranked"] :
            mult = 1
        else :
            mult = 0


        data["elop"] = round(newElo(data["elo_player"],data["difficulty"],True),2) * mult
        data["elom"] = round(newElo(data["elo_player"],data["difficulty"],False),2) * mult
        data["n_elom"] = max(0,round(data["elo_player"] +  data["elom"],2))
        data["n_elop"] = max(0,round(data["elo_player"] +  data["elop"],2))

        guess = db.session.query(tries.Tries).filter_by(id_game = current_game.id).order_by(tries.Tries.try_number).all()
        for elm in guess:
            data["guess"].append(elm.word)

        data["currenttry"] = len(guess)

        for i in range(current_game.maxtry - len(guess)):
            data["guess"].append("")   
        
        
        
        data["miss"],data['found'],data['misplace'] = classLeters(data["guess"],data['solution'])

    data["motsValides"]=[e.word for e in db.session.query(dictionnaire.Dictionnaire).filter_by(size = len(data["solution"]))]

    print("Data",data["solution"],data['ranked'])

    return jsonify(data),200
