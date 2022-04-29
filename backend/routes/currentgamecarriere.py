from flask_login import current_user
from numpy import identity
from setup import *
from flask import jsonify, request
from flask_jwt_extended import jwt_required, get_jwt_identity
from models.user import User
from models.game import Game
from models.game_carriere import Game_carriere
from models.tries import Tries
from sqlalchemy.orm import with_polymorphic


@app.route('/currentGamecarriere', methods=['GET'])
@jwt_required()
def currentGamecarriere():
    identity = get_jwt_identity()
    current_user = User.query.get(identity)
    if current_user == None: return jsonify({"error": "user not found"}), 400
    all_games_poly = with_polymorphic(game.Game, [game_carriere.Game_carriere])
    all_games = db.session.query(all_games_poly).filter(all_games_poly.Game_carriere.id_user == current_user.id,all_games_poly.Game_carriere.state == False).all()
    return jsonify(True if len(all_games)!=0 else False)