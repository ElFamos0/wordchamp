from random import *
from math import *

def newElo(elo,difficulty,won) :
    

    tab =  [9.5,9.4,9.2,8.8,8.2,7.5,6.8,6.1,5.6,5.2,5,4.8,4.4,3.9,3.2,2.5,1.8,1.2,0.8,0.6,0.5]

    if won :

        diff = int((elo - difficulty) //5 +10)
    else :

         diff = int(-(elo - difficulty) //5 +10)

    if diff < 0 :
        val = 10
    
    elif diff > 28 : 

        val = 0
    
    elif diff >= len(tab) :

        val = 0.5
    else :

        val = tab[diff]
    

    if won :

        return val
    
    else : 

        return -val



def generateGame(elo,wordlist,defaultword) :
    
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
    while len(mots_valides) == 0 and spread <=100 :

        spread += 25
        mots_valides = selectwords(target_difficulty,wordlist,spread)




    diff_liste = []
    for mot in mots_valides :

        diff_liste.append(abs(mot.difficulte - target_difficulty))


    # # Tri de Shell

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

    if len(mots_valides) == 0 :
        mot_choisi = defaultword
    else :



        indice = randint(0,len(mots_valides) -1)
        

        mot_choisi = mots_valides[indice]

    if mot_choisi.size <= 6 :
        maxtry = 6
    else :
        maxtry = mot_choisi.size

    return mot_choisi.word,maxtry,mot_choisi.difficulte