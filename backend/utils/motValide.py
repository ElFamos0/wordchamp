from flask_login import current_user
from numpy import identity
from setup import *
from flask import jsonify, request
from flask_jwt_extended import jwt_required, get_jwt_identity
from models import *
from sqlalchemy.orm import with_polymorphic
from flask import request
from sqlalchemy import desc

def motValide(essai):
    reqAllWords =  word.Word.query.all()
    allWords = [e.toDict(0, 1, 0)["word"] for e in reqAllWords]
    return jsonify(essai in allWords)
