from setup import *
from uuid import uuid4
from models.game import Game
from utils.timestamp import now

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

    def __init__(self,id_user,solution,maxtry,length):
        id = uuid4().hex
        self.id = id
        super().__init__(id,"game_normal")
        self.id_user = id_user
        self.solution = solution
        self.maxtry = maxtry
        self.length = length

    def __repr__(self):
        return '<Game_normal %r>' % self.id

    def toDict(self, id, id_user, solution, maxtry, length, date, game_type):
        dictionnaire = {}
        if id:
            dictionnaire['id']=self.id
        if id_user:
            dictionnaire['id_user']=self.id_user
        if solution:
            dictionnaire['solution']=self.solution
        if maxtry:
            dictionnaire['maxtry']=self.maxtry
        if length:
            dictionnaire['length']=self.length
        if date:
            dictionnaire['date']=self.date
        if game_type:
            dictionnaire['game_type']=self.game_type
        return dictionnaire