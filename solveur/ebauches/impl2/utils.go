package main

func countLetter(word string, letter rune) int {
	n := 0
	for _, r := range word {
		if r == letter {
			n++
		}
	}
	return n
}
