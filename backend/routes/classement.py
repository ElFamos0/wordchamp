from models.game import Game
from models.game_carriere import Game_carriere
from models.game_normal import Game_normal
from models.user import User
from setup import *
from flask import request, jsonify

@app.route('/classement', methods=['GET'])
def classement():
    reqUser = db.session.query(User).order_by(User.elo.desc()).all()
    reqUser2 = db.session.query(User).order_by(User.points.desc()).all()
    users = {"users":[e.toDict(0,1,0,1,1) for e in reqUser]}
    users2 = {"users":[e.toDict(0,1,0,1,1) for e in reqUser2]}
    for i in range(len(users["users"])):
        users["users"][i]["classement"]=i+1
        users2["users"][i]["classement"]=i+1
    return jsonify({"users":users,"users2":users2})

# all_games_poly = with_polymorphic(game.Game, [game_normal.Game_normal, game_carriere.Game_carriere])
# reqAll_games = db.session.query(all_games_poly).filter(all_games_poly.Game_normal.state == True).all()
# all_games = [e.toDict() for e in reqAll_games]