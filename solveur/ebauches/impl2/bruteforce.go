package main

// func play() {
// 	// var wg sync.WaitGroup
// 	var words []string
// 	for _, word := range allWords {
// 		if len(word) != 5 {
// 			continue
// 		}
// 		words = append(words, word)
// 	}

// 	for _, solution := range words {
// 		if len(solution) != 5 {
// 			continue
// 		}
// 		first_pass_solution(solution)
// 	}

// 	// We search for the max in the weights
// 	max := 0
// 	maxS := ""
// 	for _, w := range weights {
// 		for s, v := range w {
// 			if v > max {
// 				max = v
// 				maxS = s
// 			}
// 		}
// 	}
// 	fmt.Println(maxS)
// }

// func first_pass_solution(solution string) {
// 	attempts := []string{}

// 	var wordlist []string
// 	for _, word := range allWords {
// 		if len(solution) != len(word) {
// 			continue
// 		}
// 		if word == solution {
// 			continue
// 		}
// 		wordlist = append(wordlist, word)
// 	}

// 	minNextPossibilities := len(wordlist)
// 	minWord := ""
// 	words := wordlist
// 	for _, word := range wordlist {
// 		if len(word) != len(solution) {
// 			continue
// 		}
// 		temp := attempts
// 		temp = append(temp, word)
// 		words = next_possible_words(temp, solution, words, minNextPossibilities)
// 		if len(words) < minNextPossibilities {
// 			minNextPossibilities = len(words)
// 			minWord = word
// 		}
// 		if minNextPossibilities == 1 {
// 			break
// 		}
// 	}

// 	modify_weight(minWord, 0)
// }

// func isAttemptCorrect(attempts []string, solution string) bool {
// 	if len(attempts) == 0 {
// 		return false
// 	}
// 	return attempts[len(attempts)-1] == solution
// }

// func play_with_solution(solution string) {
// 	attempts := []string{}

// 	var wordlist []string
// 	for _, word := range allWords {
// 		if len(solution) != len(word) {
// 			continue
// 		}
// 		if word == solution {
// 			continue
// 		}
// 		wordlist = append(wordlist, word)
// 	}

// 	for !isAttemptCorrect(attempts, solution) {
// 		minNextPossibilities := len(wordlist)
// 		minWord := ""
// 		words := wordlist
// 		for _, word := range wordlist {
// 			if len(word) != len(solution) {
// 				continue
// 			}
// 			temp := attempts
// 			temp = append(temp, word)
// 			words = next_possible_words(temp, solution, words, minNextPossibilities)
// 			if len(words) < minNextPossibilities {
// 				minNextPossibilities = len(words)
// 				minWord = word
// 			}
// 		}
// 		if len(attempts) > 0 {
// 			if minWord == attempts[len(attempts)-1] {
// 				break
// 			}
// 		}
// 		attempts = append(attempts, minWord)
// 		if minNextPossibilities == 1 {
// 			break
// 		}
// 	}
// 	attempts = append(attempts, solution)
// 	for i, w := range attempts {
// 		modify_weight(w, i)
// 	}
// }

func remove_words(attempt, solution string, temp []string) []string {
	result := getWordResult(attempt, solution)
	var out []string
	for _, word := range temp {
		if len(word) != len(solution) {
			continue
		}
		keep := true
		for i, r := range attempt {
			// We check that the wrongs are okay
			if result[i] == wrong {
				amt := 0
				for j, r2 := range attempt {
					if r != r2 {
						continue
					}
					if result[j] == green || result[j] == yellow {
						amt += 1
					}
				}
				if countLetter(word, r) != amt {
					keep = false
					break
				}
			}

			// We check that the greens are okay
			if result[i] == green && word[i] != attempt[i] {
				keep = false
				break
			}

			// We check that the yellows are okay
			if result[i] == yellow && word[i] == attempt[i] {
				keep = false
				break
			}

			// We check that the yellows are okay x2
			if result[i] == yellow && !word_has_letter(word, r) {
				keep = false
				break
			}
		}
		if keep {
			out = append(out, word)
		}
	}
	return out
}

func nextWordList(attempts []string, results [][]int, wordlist []string) []string {
	// We map all the letters we have yet
	var c = make(map[rune]*letter)
	for i, attempt := range attempts {
		result := results[i]
		for _, r := range attempt {
			c[r] = &letter{
				Rune: r,
			}
		}
		for i, r := range attempt {
			l := c[r]
			if result[i] == green {
				l.Amount++
				l.MustBe = append(l.MustBe, i)
				continue
			}

			if result[i] == yellow {
				l.Amount++
				l.CannotBe = append(l.CannotBe, i)
				continue
			}
		}
	}
	var temp []string
	for _, word := range wordlist {
		passes := true
		for _, l := range c {
			tam := countLetter(word, l.Rune)
			// Mostly for yellows and wrongs
			if tam != l.Amount {
				passes = false
				break
			}
			// Yellow
			for _, p := range l.CannotBe {
				if word[p] == byte(l.Rune) {
					passes = false
					break
				}
			}
			if !passes {
				break
			}
			// Greens
			for _, p := range l.MustBe {
				if word[p] != byte(l.Rune) {
					passes = false
					break
				}
			}
			if !passes {
				break
			}
		}

		if !passes {
			continue
		}
		temp = append(temp, word)
	}
	return temp
}

func countNextPossibles(solution string, wordlist []string, currentMin int, attempts ...string) int {
	// We map all the letters we have yet
	var c = make(map[rune]*letter)
	for _, attempt := range attempts {
		result := getWordResult(attempt, solution)
		for _, r := range attempt {
			c[r] = &letter{
				Rune: r,
			}
		}
		for i, r := range attempt {
			l := c[r]
			if result[i] == green {
				l.Amount++
				l.MustBe = append(l.MustBe, i)
				continue
			}

			if result[i] == yellow {
				l.Amount++
				l.CannotBe = append(l.CannotBe, i)
				continue
			}
		}
	}

	var amt int
	for _, word := range wordlist {

		passes := true
		for _, l := range c {
			tam := countLetter(word, l.Rune)
			// Mostly for yellows and wrongs
			if tam != l.Amount {
				passes = false
				break
			}
			// Yellow
			for _, p := range l.CannotBe {
				if word[p] == byte(l.Rune) {
					passes = false
					break
				}
			}
			if !passes {
				break
			}
			// Greens
			for _, p := range l.MustBe {
				if word[p] != byte(l.Rune) {
					passes = false
					break
				}
			}
			if !passes {
				break
			}
		}

		if !passes {
			continue
		}
		amt++

		if amt > currentMin {
			return amt
		}
	}
	return amt
}
