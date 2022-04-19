from setup import *
from setup import db
from uuid import uuid4

class Games(db.Model):
    __tablename__ = 'games'
    id = db.Column(db.String(40), primary_key=True)
    game_type = db.Column(db.String(40), primary_key=True)
    state = db.Column(db.Boolean, nullable=False)
    date = db.Column(db.Integer, nullable=False)

    def __init__(self, game_type,date):
        self.id = uuid4().hex
        self.game_type = game_type
        self.date = date
        self.state = False

    def __repr__(self):
        return '<Game %r>' % self.id
