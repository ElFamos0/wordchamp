from setup import *
from uuid import uuid4
from models.game import Game

class Game_normal(Game):
    __tablename__ = 'games_normal'
    id = db.Column(db.String(40), db.ForeignKey("games.id"), primary_key=True)
    id_user = db.Column(db.String(40), db.ForeignKey("users.id"),nullable=False)
    solution = db.Column(db.String(40), nullable=False)
    maxtry = db.Column(db.Integer, nullable=False)
    length = db.Column(db.Integer, nullable=False)

    __mapper_args__ = {
        'polymorphic_identity':'game_normal',
    }

    def __init__(self,id_user,solution,maxtry,length,date):
        id = uuid4().hex
        self.id = id
        super().__init__(id,"game_normal",date)
        self.id_user = id_user
        self.solution = solution
        self.maxtry = maxtry
        self.length = length

    def __repr__(self):
        return '<Game_normal %r>' % self.id

    def toDict(self):
        dictionnaire = {}
        dictionnaire['id']=self.id
        dictionnaire['id_user']=self.id_user
        dictionnaire['solution']=self.solution
        dictionnaire['maxtry']=self.maxtry
        dictionnaire['length']=self.length
        dictionnaire['date']=self.date
        return dictionnaire