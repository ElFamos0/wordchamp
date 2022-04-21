from setup import *
from flask import jsonify, send_from_directory, request
from flask_jwt_extended import jwt_required, get_jwt_identity
from models.user import User
import os
from snowflake import SnowflakeGenerator

avatar_gen = SnowflakeGenerator(666)

default_path = "avatar/default.png"
# sanity check route
@app.route('/avatar/<id>', methods=['GET'])
def avatar(id):
    user = User.query.get(id)
    name = user.avatar_name()
    folder = f"static/avatar/{id}/{name}.png"
    file = f"avatar/{id}/{name}.png"
    if not os.path.exists(folder):
        return send_from_directory('static', default_path)
    return send_from_directory('static', file)


@app.route('/profile_set/avatar', methods = ['POST'])
@jwt_required()
def set_avatar():
    user_id = get_jwt_identity()
    user = User.query.get(user_id)
    if user == None: return jsonify({"error": "user not found"}), 400
    
    f = request.files['file']
    if f:
        folder = f"static/avatar/{user_id}"
        if not os.path.exists(folder):
            os.mkdir(folder)
        else:
            L = os.listdir(folder)
            for file in L:
                os.remove(f"{folder}/{file}")
        f.save(f"{folder}/{next(avatar_gen)}.png")
        return jsonify({'success': True}), 200
    else:
        return jsonify({"error": "no file"}), 400