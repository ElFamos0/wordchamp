from setup import *
from models.word import Word
from random import randrange

def getrandomword():
    listemot = Word.query.all()
    n = len(listemot)
    i = randrange(0, n)
    return listemot[i].word

