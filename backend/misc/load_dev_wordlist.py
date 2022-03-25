from setup import *
from models.word import Word

def do_it():
    FILE = "misc/dev_wordlist"
    file = open(FILE, "r")

    # We load the wordlist into the database
    for line in file.readlines():
        word = line.strip()
        if len(word) > 0:
            w = Word(word)
            db.session().add(w)
    db.session().commit()
    file.close()