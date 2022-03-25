from setup import *
from models.word import Word

def do_it():
    FILE = "dev_wordlist.txt"
    file = open(FILE, "r")

    # We load the wordlist into the database
    for line in file.readlines():
        word = line.strip()
        if len(word) > 0:
            w = Word(word)
            db.session.add(w)
    
    file.close()