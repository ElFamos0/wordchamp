from tabnanny import check
from routes.motValide import motValide
from flask_login import current_user
from numpy import identity
from setup import *
from flask import jsonify, request
from flask_jwt_extended import jwt_required, get_jwt_identity
from models import *
from sqlalchemy.orm import with_polymorphic
from flask import request
from sqlalchemy import desc
from utils.wordcheck import check_word
from utils.classLeters import classLeters



@app.route('/send_try_carriere', methods=['POST'])
@jwt_required()
def send_try_carriere():
    identity = get_jwt_identity()
    current_user = user.User.query.get(identity)
    if current_user == None: return jsonify({"error": "user not found"}), 400

    data = request.json["data"]

    if not(motValide(data)):
        return jsonify({"error": "word not in DB"}),400

    all_games_poly = with_polymorphic(game.Game, [game_carriere.Game_carriere])
    all_games = db.session.query(all_games_poly).filter(all_games_poly.Game_carriere.id_user == current_user.id,all_games_poly.Game_carriere.state == False).order_by(desc(all_games_poly.Game_carriere.date)).all()

    gam = all_games[0]

    for i in range(1,len(all_games)) :
        current_user.elo += all_games[i].endGame(False) 
    
    db.session.commit()

    
    id_game = gam.id
    maxtry = gam.maxtry
    solution = gam.solution

    all_tries = tries.Tries.query.filter(tries.Tries.id_game == id_game).all()

    if len(data) > len(solution)  :

        data = data[:len(solution)]
        
    elif len(data) < len(solution) :

        data += 'A' * (len(solution) - len(data))

    colors = check_word(data, solution)
    guesses = []
    for elm in db.session.query(tries.Tries).filter_by(id_game = gam.id).order_by(tries.Tries.try_number).all():
        guesses.append(elm.word)
    guesses.append(data)
    guessedLetters = {}
    guessedLetters["miss"],guessedLetters['found'],guessedLetters['misplace'] = classLeters(guesses, gam.solution)


    if data == solution :

        newTry = tries.Tries(id_game,data,len(all_tries) + 1)
        db.session.add(newTry)

        current_user.elo += round(gam.endGame(True,gam.ranked),2)
        current_user.elo = max(0,round(current_user.elo,2))
        current_user.points=current_user.points+1

        db.session.commit()


        return jsonify({"success": True, "ended": True, "victory": True, "colors":colors, "guessedletters":guessedLetters}),200

    elif len(all_tries) + 1 >= maxtry :

        newTry = tries.Tries(id_game,data,len(all_tries) + 1)
        db.session.add(newTry)

        current_user.elo += round(gam.endGame(False,gam.ranked),2)
        current_user.elo = max(0,round(current_user.elo,2))

        db.session.commit()

        return jsonify({"success": True, "ended": True, "victory": False, "colors":colors, "solution":solution, "guessedletters":guessedLetters}),200
    
    else :

        newTry = tries.Tries(id_game,data,len(all_tries) + 1)
        db.session.add(newTry)

        db.session.commit()

        colors = check_word(data,solution)
        return jsonify({"success": True, "ended": False, "victory": False, "colors":colors, "guessedletters":guessedLetters}),200

