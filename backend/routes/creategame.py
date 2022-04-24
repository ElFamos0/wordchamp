from numpy import identity
from setup import *
from flask import jsonify, request
from flask_jwt_extended import jwt_required, get_jwt_identity
from models.user import User
from models.game import Game
from models.game_normal import Game_normal


@app.route('/creategame', methods=['GET'])
@jwt_required()
def creategame():
    identity = get_jwt_identity()
    user = User.query.get(identity)
    if user == None: return jsonify({"error": "user not found"}), 400
   
    newGameNormal = Game_normal(user.id,"dentifrice",6,10,"21022021")
    db.session.add(newGameNormal)
 
    db.session.commit()

    return jsonify({"success": "game created"}),200
