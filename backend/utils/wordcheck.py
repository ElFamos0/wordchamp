from setup import *

"""
Fonctions qui vont nous permettre de voir si le mot est dans la db et qui vont nous permettre de donner tous les indices sur le mots
"""

def check_word(word,solution):
    # 0 => gris
    # 1 => jaune
    # 2 => rouge
    colors = []    
    compte = {}
    assert(len(word) == len(solution))

    for i in range(len(solution)):
        compte[solution[i]] = compte.get(solution[i],0) + 1
        if (word[i] == solution[i]):
            colors.append(2)
            compte[solution[i]] -= 1
        else:
            colors.append(0)
    for i in range(len(solution)):
        if (colors[i] == 0) :
            if compte.get(word[i],0) > 0:
                colors[i] = 1
                compte[word[i]] -= 1
    return colors