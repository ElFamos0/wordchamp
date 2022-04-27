from setup import *

"""
Fonctions qui vont nous permettre de voir si le mot est dans la db et qui vont nous permettre de donner tous les indices sur le mots
"""

def check_word(word,solution):
    colortab = []    
    assert(len(word) == len(solution))
    for i in range(len(word)):
        if word[i] not in solution:
            colortab.append(0)
        elif word[i] == solution[i]:
            colortab.append(2)
        elif word[i] in solution[i:]:
            #a modifier les conditions sont plus complexes que ça
            colortab.append(1)
    return colortab

