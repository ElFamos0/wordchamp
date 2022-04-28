from models.game import Game
from models.game_survie import Game_survie
from models.game_normal import Game_normal
from models.user import User
from setup import *
from flask import request, jsonify

@app.route('/classement', methods=['GET'])
def classement():
    reqUser = db.session.query(User).order_by(User.points.desc()).all()
    users = {"users":[e.toDict(0,1,0,1,0) for e in reqUser]}
    for i in range(len(users["users"])):
        users["users"][i]["classement"]=i+1
    return jsonify(users)

# all_games_poly = with_polymorphic(game.Game, [game_normal.Game_normal, game_survie.Game_survie])
# reqAll_games = db.session.query(all_games_poly).filter(all_games_poly.Game_normal.state == True).all()
# all_games = [e.toDict() for e in reqAll_games]