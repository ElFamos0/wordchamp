from setup import *
from flask import jsonify, send_from_directory
from flask_jwt_extended import jwt_required, get_jwt_identity
from models.user import User
import os

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