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


@app.route('/choicecarriere', methods=['GET'])
@jwt_required()
def choicecarriere():
    
    print(1)
    identity = get_jwt_identity()
    current_user = User.query.get(identity)
    if current_user == None: return jsonify({"error": "user not found"}), 400

    data = {"elo" : current_user.elo}
    return jsonify(data),200
