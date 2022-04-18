from setup import *
from flask import request, jsonify
from models.user import User
from flask_jwt_extended import jwt_required, create_access_token, get_jwt_identity

@app.route('/login', methods=['POST'])
def login():
    #print(request.json)
    username = request.json["username"]
    password = request.json["password"]
    if password == "" or username == "":
        return jsonify({"error": "empty username or password"}), 400
    
    user = User.query.filter_by(username=username).first()
    #print(user)
    if user is None:
        return jsonify({"error": "username does not exist"}), 401
    #print(user.password_hash)
    if not user.check_password(password):
        return jsonify({"error": "wrong password"}), 401
    #print("logged in")
    access_token = create_access_token(identity=user.id)
    return jsonify({"success": "logged in", "id": user.id, "token": access_token}), 200

@app.route('/verify-token', methods=['POST'])
@jwt_required()
def verify_token():
    return jsonify({'success': True}), 200