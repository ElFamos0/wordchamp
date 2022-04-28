from random import *
from math import *

def newElo(elo,difficulty,won) :
    
    diff = abs(elo - difficulty)

    if diff > 50 :

        if won :
            return  0.24
        else :
            return -0.24
    
    else :

        if won :
            return (0.00101*(diff**2)-0.155*diff+5.47762)
        else :
            return -(0.00101*(diff**2)-0.155*diff+5.47762)


def generateGame(elo,wordlist) :
    
    target_difficulty = elo
    spread= 25

    def selectwords(target_difficulty,wordlist,spread) :

        mots_valides = []

        for mot in wordlist :

            if abs(mot.difficulte - target_difficulty ) <= spread and mot.size >= 5 :

                if (mot.gram =="ADJ" or mot.gram == "NOM") and mot.nombre == "s" :
                    mots_valides.append(mot)
        
                elif mot.gram == "PRO" and (mot.genre == "m" or mot.genre == "f") :

                    mots_valides.append(mot)
        
                elif (mot.gram == "VER" or mot.gram == "AUX") and (mot.conjug[:3] == "inf" or (mot.conjug[:3] == "par" and mot.nombre == 's')) :

                    mots_valides.append(mot)
        
                elif mot.gram == "ADV" or mot.gram =="PRE" or mot.gram =="CON" or mot.gram =="ONO"   :

                    mots_valides.append(mot)

        return mots_valides


    mots_valides = selectwords(target_difficulty,wordlist,spread)
    while len(mots_valides) == 0 :

        spread += 25
        mots_valides = selectwords(target_difficulty,wordlist,spread)




    diff_liste = []
    for mot in mots_valides :

        diff_liste.append(abs(mot.difficulte - target_difficulty))


    # Tri de Shell

    # gaps = [701, 301, 132, 57, 23, 10, 4, 1]

    # gap = gaps[0]
    # while gap<len(diff_liste):
    #     gap = int(gap*2.3)
    #     gaps = [gap] + gaps

    
    
    # n = len(diff_liste)
    # for m in gaps:
    #     for r in range(m):
        
    #         for i in range (r + m, n, m):
    #             j = i
    #             x_diff = diff_liste[i]
    #             x_mot = mots_valides[i]

    #             while j > r and diff_liste[j-m] > x_diff:
    #                 diff_liste[j] = diff_liste[j-m]
    #                 mots_valides[j] = mots_valides[j-m]
    #                 j = j - m

    #             diff_liste[j] = x_diff
    #             mots_valides[j] = x_mot


    indice = randint(0,len(mots_valides) -1)
    
    mot_choisi = mots_valides[indice]

    if mot_choisi.size <= 6 :
        maxtry = 6
    elif mot_choisi.size <= 8 :
        maxtry = 7
    else :
        maxtry = 8

    return mot_choisi.word,maxtry,mot_choisi.size





    
