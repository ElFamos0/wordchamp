from numpy import identity
from setup import *
from flask import jsonify, request
from flask_jwt_extended import jwt_required, get_jwt_identity
from models.user import User


@app.route('/creategame', methods=['GET'])
@jwt_required()
def creategame():
    identity = get_jwt_identity()
    user = User.query.get(identity)
    if user == None: return jsonify({"error": "user not found"}), 400
    print(user.username)
