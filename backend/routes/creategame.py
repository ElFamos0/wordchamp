from flask_login import current_user
from numpy import identity
from setup import *
from flask import jsonify, request
from flask_jwt_extended import jwt_required, get_jwt_identity
from models.user import User
from models.game import Game
from models.game_normal import Game_normal
from utils.getword import getrandomword, getrandomwordbysize
from sqlalchemy.orm import with_polymorphic


@app.route('/creategame/<taille>', methods=['GET'])
@jwt_required()
def creategame(taille):
    identity = get_jwt_identity()
    current_user = User.query.get(identity)
    if current_user == None: return jsonify({"error": "user not found"}), 400
    all_games_poly = with_polymorphic(game.Game, [game_normal.Game_normal, game_survie.Game_survie])
    all_games = db.session.query(all_games_poly).filter(all_games_poly.Game_normal.id_user == current_user.id).all()
    print(all_games[0].game_type)
    if len(all_games) == 0:
        word = getrandomwordbysize(taille)
        newGameNormal = game_normal.Game_normal(current_user.id,word,len(word),6)       #(last attribut = date en timestamp)
        db.session.add(newGameNormal)
        db.session.commit()
        
    else:
        pass
    return jsonify({"success": "game created"}),200
