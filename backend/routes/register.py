from setup import *
from flask import request, jsonify
from models.user import User

@app.route('/register', methods=['POST'])
def register():
    print(request.json)
    username = request.json["username"]
    password = request.json["password"]
    if password == "" or username == "":
        return jsonify({"error": "empty username or password"}), 400
    if User.query.filter_by(username=username).count() > 0:
        return jsonify({"error": "username already exists"}), 400
    newUsr = User(username, password)
    db.session.add(newUsr)
    db.session.commit()
    #print("new user created")
    return jsonify({"success": "user created"}), 200
