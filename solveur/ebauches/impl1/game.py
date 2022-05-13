import random

class Letter:
    def __init__(self, letter="", place=0, state="0"):
        self.letter = letter
        self.places = {place:state}

    def add(self, place, state):
        self.places[place] = state

    def __eq__(self, other):
        if isinstance(other, self.__class__):
            return self.letter == other.letter
        elif isinstance(other, str):
            return self.letter == other
        else:
            return False

    def __repr__(self) -> str:
        return f"{self.letter} at {self.places} / {self.states}"

    def isMissPlaced(self, place):
        if place in self.places:
            return self.places[place] == "1"
    
    def isRight(self, place):
        if place in self.places:
            return self.places[place] == "2"
    
    def hasRight(self):
        for key in self.places:
            if self.places[key] == "2":
                return True
        return False

    def hasMissPlaces(self):
        for key in self.places:
            if self.places[key] == "1":
                return True
        return False

    def hasWrong(self):
        for key in self.places:
            if self.places[key] == "0":
                return True
        return False
    
    def amountOf(self):
        r = 0
        for key in self.places:
            if self.places[key] != "0":
                r += 1
        return r


class Wordle:
    def __init__(self, guesses=[], results=[], dico=[]):
        self.guesses = guesses
        self.results = results
        self.dict = dico
        # Useful stuff
        self.letters = []

    def add_guess(self, guess):
        self.guesses.append(guess)
    
    def add_result(self, result):
        self.results.append(result)

    def analyze_result(self, result, guess):
        for i in range(len(result)):
            l = Letter(guess[i], i, result[i])
            if l not in self.letters:
                self.letters.append(l)
            else :
                self.letters[self.letters.index(l)].add(i, result[i])
    
    def allRightLetters(self):
        r = []
        for l in self.letters:
            if l.hasRight():
                r.append(l)
        return r
    
    def allMissplacedLetters(self):
        r = []
        for l in self.letters:
            if l.hasMissPlaces():
                r.append(l)
        return r
    
    def allWrongLetters(self):
        r = []
        for l in self.letters:
            if l.hasWrong():
                r.append(l)
        return r

    def checkRightsPlacement(self, word):
        rights = self.allRightLetters()
        for l in rights:
            if l.letter not in word:
                return False
            for key in l.places:
                if not l.isRight(key):
                    continue
                if word[key] != l.letter:
                    return False
        return True

    def checkMissedPlacements(self, word):
        mp = self.allMissplacedLetters()
        for l in mp:
            if l.letter not in word:
                return False
            for key in l.places:
                if not l.isMissPlaced(key):
                    continue
                if word[key] == l.letter:
                    return False
        return True

    def checkWrongPlacements(self, word):
        w = self.allWrongLetters()
        for l in w:
            if word.count(l.letter) > l.amountOf():
                return False
        return True
    
    def list_possible_words(self, size=0):
        words = []
        
        for word in self.dict:
            if len(word) != size: continue
            if not self.checkRightsPlacement(word): continue
            if not self.checkMissedPlacements(word): continue
            if not self.checkWrongPlacements(word): continue
                
            words.append(word)
            
        return words
    
    def find_next_best_word(self, size=0):
        words = self.list_possible_words(size)
        if len(words) == 0:
            return None
        return random.choice(words)