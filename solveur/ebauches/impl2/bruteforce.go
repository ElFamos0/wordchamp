package main

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
			if tam < l.Amount {
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
