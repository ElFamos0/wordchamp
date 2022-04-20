from setup import *
from setup import db
from uuid import uuid4

class Game(db.Model):
    __tablename__ = 'games'
    id = db.Column(db.String(40), primary_key=True)
    game_type = db.Column(db.String(40))
    state = db.Column(db.Boolean, nullable=False)
    date = db.Column(db.Integer, nullable=False)

    __mapper_args__ = {
        'polymorphic_identity':'games',
        'polymorphic_on':game_type
    }

    def __init__(self, game_type,date):
        self.id = uuid4().hex
        self.game_type = game_type
        self.date = date
        self.state = False

    def __repr__(self):
        return '<Game %r>' % self.id
