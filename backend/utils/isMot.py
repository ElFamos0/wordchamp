from flask_login import current_user
from numpy import identity
from setup import *
from flask import jsonify, request
from flask_jwt_extended import jwt_required, get_jwt_identity
from models import *
from sqlalchemy.orm import with_polymorphic
from flask import request
from sqlalchemy import desc

def isMot(essai):
    reqAllWords =  dictionnaire.Dictionnaire.query.filter_by(word=essai).all()
    return jsonify(True if len(reqAllWords)>0 else False)
