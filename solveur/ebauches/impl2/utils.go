package main

func word_has_letter(word string, letter rune) bool {
	for _, r := range word {
		if r == letter {
			return true
		}
	}
	return false
}

func count_letter(word string, letter rune) int {
	n := 0
	for _, r := range word {
		if r == letter {
			n++
		}
	}
	return n
}
