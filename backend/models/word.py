from setup import *
from uuid import uuid4

class Word(db.Model):
    __tablename__ = 'words'
    id = db.Column(db.String(40), primary_key=True)
    word = db.Column(db.String(20), nullable=False)
    size = db.Column(db.Integer, nullable=False)

    def __init__(self, word):
        self.id = uuid4().hex
        self.word = word
        self.size = len(word)

    def __repr__(self):
        return '<Word %r>' % self.word

    def toDict(self, id, word, size):
        dictionnaire = {}
        if id:
            dictionnaire["id"]=self.id
        if word:
            dictionnaire["word"]=self.word
        if size:
            dictionnaire["size"]=self.size
        return dictionnaire
