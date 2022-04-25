from setup import *
from uuid import uuid4
from models.game import Game

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

    def __init__(self,id_user,maxtry,length,date):
        id = uuid4().hex
        self.id = id
        super().__init__(id,"game_survie",date)
        self.id_user = id_user
        self.maxtry = maxtry
        self.length = length
        self.score = 0

    def __repr__(self):
        return '<Game_normal %r>' % self.id

    def toDict(self):
        dictionnaire = {}
        dictionnaire['id']=self.id
        dictionnaire['id_user']=self.id_user
        dictionnaire['score']=self.score
        dictionnaire['maxtry']=self.maxtry
        dictionnaire['length']=self.length
        dictionnaire['date']=self.date
        return dictionnaire
