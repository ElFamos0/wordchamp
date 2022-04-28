from setup import *
from models.word import Word
from models.dictionnaire import Dictionnaire

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



def normalize(word) :

    word = word.upper()
    a_string = "àâä".upper()
    e_string = "éèêë".upper()
    o_string = "ôö".upper()
    i_string = "îï".upper()
    u_string = "ùûü".upper()
    c_string = "ç".upper()
    oe_string = "œ".upper()
    alph = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    strange = "\n\t"
    state = True

    for letter in word :
        if letter in a_string :
            word = word.replace(letter,"A")
        elif letter in e_string :
            word =  word.replace(letter,"E")
        elif letter in o_string :
            word = word.replace(letter,"O")
        elif letter in i_string :
            word = word.replace(letter,"I")
        elif letter in u_string :
            word = word.replace(letter,"U")
        elif letter in c_string :
            word = word.replace(letter,"C")
        elif letter in oe_string :
            word = word.replace(letter,"OE")
        elif letter in strange :
            word = word.replace(letter,"")

    for letter in word :
        if letter not in alph :
            state = False

    return word,state
    




def do_it_bis() :

    FILE = "misc/lex.txt"
    file = open(FILE, "r")

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

            nombre = None
            conjug = None
            genre = None
            if liste_param[4] != "" :
                genre = liste_param[4]
            if liste_param[5] != "" :
                nombre = liste_param[5]
            if liste_param[10] != "" :
                conjug = liste_param[10]

            dic = Dictionnaire(word,freq,gram,genre,nombre,conjug)
            db.session().add(dic)
    db.session().commit()
    file.close()