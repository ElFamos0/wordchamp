from setup import *
from uuid import uuid4
from models.game import Game
from utils.timestamp import now

class Game_survie(Game):
    __tablename__ = 'games_survie'
    id = db.Column(db.String(40), db.ForeignKey("games.id"), primary_key=True)
    id_user = db.Column(db.String(40), db.ForeignKey("users.id"),nullable=False)
    maxtry = db.Column(db.Integer, nullable=False)
    length = db.Column(db.Integer, nullable=False)
    score = db.Column(db.Integer, nullable=False)

    __mapper_args__ = {
        'polymorphic_identity':'game_survie',
    }

    def __init__(self,id_user,maxtry,length):
        id = uuid4().hex
        self.id = id
        super().__init__(id,"game_survie")
        self.id_user = id_user
        self.maxtry = maxtry
        self.length = length
        self.score = 0

    def __repr__(self):
        return '<Game_normal %r>' % self.id

    def toDict(self, id, id_user, score, maxtry, length, date):
        dictionnaire = {}
        if id:
            dictionnaire['id']=self.id
        if id_user:
            dictionnaire['id_user']=self.id_user
        if score:
            dictionnaire['solution']=self.score
        if maxtry:
            dictionnaire['maxtry']=self.maxtry
        if length:
            dictionnaire['length']=self.length
        if date:
            dictionnaire['date']=self.date
        return dictionnaire