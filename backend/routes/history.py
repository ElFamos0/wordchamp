from models.game_normal import Game_normal
from setup import *
from flask import request, jsonify
# from utils import estGagnee

@app.route('/history', methods=['GET'])
def history():
    current_user = ""
    entries = []
    requete = Game_normal.query.filter_by(id_user=current_user).all()
    for game in requete:
        temp={"id":"", "guesses":[], "solution":"", "result":""}
        guesses=[]
        temp.solution = game.solution
        # temp.result = estGagnee(guesses, game.solution)
        entries.append(temp)
    return 'test'
    # à récup dans le DB plutôt que de l'écrire en dur
    return jsonify({
        "entries":[
            {"id":"1", "guesses":[{"id":"1", "word":"test"}, {"id":"2", "word":"zero"}], "solution":"Oulala", "result":"Victoire"},
            {"id":"2", "guesses":[{"id":"1", "word":"test"}, {"id":"2", "word":"zizi"}, {"id":"3", "word":"pipi"}], "solution":"MaitreSauceur", "result":"Défaite"},
            {"id":"3", "guesses":[{"id":"1", "word":"yooo"}], "solution":"sérieuxmec", "result":"NULMDR"},
            {"id":"4", "guesses":[], "solution":"sheeeeeeeeeeeeeeeeeeesh", "result":"Défiak"},
        ]
        })