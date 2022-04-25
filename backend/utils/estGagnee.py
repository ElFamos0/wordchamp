def estGagnee(entry):
    solution = entry["solution"]
    guesses = entry["guesses"]
    lastGuessWord = ""
    if guesses:
        lastGuess = guesses[-1]
        lastGuessWord = lastGuess["word"]
    return True if lastGuessWord==solution else False