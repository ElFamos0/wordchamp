from dict import dict
from game import Wordle
import sys, getopt

argv = sys.argv[1:]
wordlength = 5
try:
    opts, args = getopt.getopt(argv,"hs:",["size="])
except getopt.GetoptError:
    print('this.py -s <size>')
    sys.exit(2)
for opt, arg in opts:
    if opt == '-h':
        print('this.py -s <size>')
        sys.exit()
    elif opt in ("-s", "--size"):
        wordlength = int(arg)

g = Wordle(dico=dict)

for i in range(wordlength):
    guess = g.find_next_best_word(wordlength)
    print(guess)
    result = input("")
    if not "0" in result and not "1" in result:
        break
    g.add_guess(guess)
    g.add_result(result)
    g.analyze_result(result, guess)
