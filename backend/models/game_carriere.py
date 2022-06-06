from setup import *
from uuid import uuid4
from models.game import Game
from models import dictionnaire
from models import user
from utils.timestamp import now
from utils.eloFunctions import *

class Game_carriere(Game):
    __tablename__ = 'games_carriere'
    id = db.Column(db.String(40), db.ForeignKey("games.id"), primary_key=True)
    id_user = db.Column(db.String(40), db.ForeignKey("users.id"),nullable=False)
    solution = db.Column(db.String(40), nullable=False)
    maxtry = db.Column(db.Integer, nullable=False)
    length = db.Column(db.Integer, nullable=False)
    difficulty = db.Column(db.Float, nullable = False)
    won = db.Column(db.Boolean, nullable = True)
    elo_player =  db.Column(db.Float, nullable = True)
    ranked = db.Column(db.Boolean, nullable = False)

    __mapper_args__ = {
        'polymorphic_identity':'game_carriere',
    }

    def __init__(self,id_user,ranked):

        current_user =  user.User.query.get(id_user)
        elo = current_user.elo
        spread = int(elo*0.326)
        if spread < 30 :
            spread = 30

        defaultword = dictionnaire.Dictionnaire.query.filter(dictionnaire.Dictionnaire.word == "TRICHEUR").first()
        
        id = uuid4().hex
        self.id = id
        super().__init__(id,"game_carriere")
        self.id_user = id_user
        self.elo_player = elo
        self.solution,self.maxtry,self.difficulty = generateGame(self.elo_player,dictionnaire.Dictionnaire.query.filter(dictionnaire.Dictionnaire.size > 4,dictionnaire.Dictionnaire.difficulte > self.elo_player - spread,dictionnaire.Dictionnaire.difficulte < self.elo_player + spread).all(),defaultword)
        self.length = len(self.solution)
        self.ranked = ranked
        
        
    def __repr__(self):
        return '<Game_normal %r>' % self.id

    def endGame(self,won,ranked) :

        self.won = won
        self.state = True
        if ranked :
            return (newElo(self.elo_player,self.difficulty,won))
        else :
            return 0




    def toDict(self, id, id_user, difficulty, maxtry, length, date,solution,won,elo_player,ranked, game_type=0):
        dictionnaire = {}
        if id:
            dictionnaire['id']=self.id
        if id_user:
            dictionnaire['id_user']=self.id_user
        if difficulty:
            dictionnaire['difficulty']=self.difficulty
        if maxtry:
            dictionnaire['maxtry']=self.maxtry
        if length:
            dictionnaire['length']=self.length
        if date:
            dictionnaire['date']=self.date
        if solution :
            dictionnaire['solution'] = self.solution
        if won :
            dictionnaire['won'] = self.won
        if elo_player :
            dictionnaire['elo_player'] = self.elo_player
        if won :
            dictionnaire['ranked'] = self.ranked
        if game_type:
            dictionnaire['game_type']=self.game_type
        return dictionnaire