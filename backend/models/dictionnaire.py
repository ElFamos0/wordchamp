from setup import *
from uuid import uuid4
from utils.evalDifficulty import set_difficulte

class Dictionnaire(db.Model):
    __tablename__ = 'dictionnaire'
    id = db.Column(db.String(40), primary_key=True)
    word = db.Column(db.String(20), nullable=False)
    size = db.Column(db.Integer, nullable=False)
    freq = db.Column(db.Float,nullable= False)
    gram = db.Column(db.String(20),nullable= False)
    genre = db.Column(db.String(20),nullable= True)
    nombre = db.Column(db.String(20),nullable= True)
    conjug = db.Column(db.String(20),nullable= True)
    difficulte = db.Column(db.Float,nullable= False)


    def __init__(self, word,freq,gram,genre = None,nombre = None,conjug = None):
        self.id = uuid4().hex
        self.word = word
        self.size = len(word)
        self.freq = freq
        self.gram = gram
        self.difficulte = set_difficulte(word,freq)
        if genre != None :
            self.genre = genre
        if nombre != None :
            self.nombre = nombre
        if conjug != None :
            self.conjug = conjug

    def __repr__(self):
        return '<Word %r>' % self.word

    def toDict(self, id, word, size,freq,difficulte,gram,genre,nombre,conjug):
        dico = {}
        if id:
            dico["id"]=self.id
        if word:
            dico["word"]=self.word
        if size:
            dico["size"]=self.size
        if freq :
            dico["freq"] = self.freq
        if gram :
            dico["gram"] = self.gram
        if genre :
            dico["genre"] = self.genre
        if nombre :
            dico["nombre"] = self.nombre
        if conjug :
            dico["conjug"] = self.conjug   
        if difficulte :
            dico["difficulte"] = self.difficulte

        return dico
