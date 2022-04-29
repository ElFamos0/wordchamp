from setup import *
from models.word import Word
from models.dictionnaire import Dictionnaire
import unicodedata


def do_it():
    FILE = "misc/dev_wordlist"
    file = open(FILE, "r", encoding='utf-8')

    # We load the wordlist into the database
    for line in file.readlines():
        word = line.strip()
        if len(word) > 0:
            w = Word(word)
            db.session().add(w)
    db.session().commit()
    file.close()


def normalize(word) :

    
    word = unicodedata.normalize('NFKD', word).encode('ascii', 'ignore').decode('utf-8')

    alph = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    word = word.upper()

    state = True

    for letter in word :
        if letter not in alph :
            state = False

    return word,state

def do_it_bis() :

    FILE = "misc/lex.txt"
    file = open(FILE, "r", encoding='utf-8')
    count = 0

    # We load the wordlist into the database
    for line in file.readlines():
        ligne = line.strip()
        liste_param = []
        compteur = 0
        temp = ""
        i = 0
        while compteur < 11 :
            if ligne[i] != '\t' and ligne[i] != ' ' :
                temp +=ligne[i]
            
            elif ligne[i] == ' ' :

                pass

            else :
                liste_param.append(temp)
                compteur += 1
                temp = ""
            i+=1
        
        word,state = normalize(liste_param[0])
        freq = float(liste_param[9])
        gram = liste_param[3][:3]

        if len(word) > 0 and len(word) <= 10 and state:
            
            count +=1
            nombre = None
            conjug = None
            genre = None
            if liste_param[4] != "" :
                genre = liste_param[4]
            if liste_param[5] != "" :
                nombre = liste_param[5]
            if liste_param[10] != "" :
                taille = min(20,len(liste_param[10]) - 1)
                conjug = liste_param[10][:taille]

            dic = Dictionnaire(word,freq,gram,genre,nombre,conjug)
            db.session().add(dic)

            if count % 100 == 0 :
                db.session().commit()
    
    file.close()