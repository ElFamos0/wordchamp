from numpy import identity
from setup import *
from flask import jsonify, request
from flask_jwt_extended import jwt_required, get_jwt_identity
from models.user import User
from models.game import Game
from models.game_normal import Game_normal
from uuid import uuid4

@app.route('/creategame', methods=['GET'])
@jwt_required()
def creategame():
    identity = get_jwt_identity()
    user = User.query.get(identity)
    if user == None: return jsonify({"error": "user not found"}), 400
   
    id = uuid4().hex
    newGame = Game(id,"normal","21022021")
    newGameNormal = Game_normal(id,user.id,"dentifrice",6,10)
    db.session.add(newGame)
    db.session.add(newGameNormal)
    db.session.commit()

    return jsonify({"success": "game created"}),200
