from setup import *

class Word(db.Model):
    __tablename__ = 'words'
    word = db.Column(db.String(40), primary_key=True)
    size = db.Column(db.Integer, nullable=False)

    def __init__(self, word):
        self.word = word
        self.size = len(word)

    def __repr__(self):
        return '<Word %r>' % self.word
