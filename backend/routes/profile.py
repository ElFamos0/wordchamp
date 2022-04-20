from setup import *
from flask import jsonify, request
from flask_jwt_extended import jwt_required, get_jwt_identity
from models.user import User

@app.route('/profile_set/username', methods = ['POST'])
@jwt_required()
def set_username():
    new_username = request.json["username"]
    if User.query.filter_by(username=new_username).count() > 0:
        return jsonify({"error": "username already taken"}), 400
    user_id = get_jwt_identity()
    user = User.query.get(user_id)
    user.username = new_username
    db.session.commit()
    return jsonify({"success": "username set", "new_username": user.username}), 200