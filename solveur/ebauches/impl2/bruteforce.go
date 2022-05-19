package main

import (
	"sync"
)

func play() {
	var wg sync.WaitGroup
	for i, solution := range allWords {
		if i%100 == 0 {
			wg.Wait()
		}
		wg.Add(1)
		go func(s string) {
			first_pass_solution(s)
			wg.Done()
		}(solution)
	}
	wg.Wait()
}

func first_pass_solution(solution string) {
	attempts := []string{}

	var wordlist []string
	for _, word := range allWords {
		if len(solution) != len(word) {
			continue
		}
		if word == solution {
			continue
		}
		wordlist = append(wordlist, word)
	}

	minNextPossibilities := len(wordlist)
	minWord := ""
	words := wordlist
	for _, word := range wordlist {
		if len(word) != len(solution) {
			continue
		}
		temp := attempts
		temp = append(temp, word)
		words = next_possible_words(temp, solution, words)
		if len(words) < minNextPossibilities {
			minNextPossibilities = len(words)
			minWord = word
		}
	}

	modify_weight(minWord, 0)
}

func isAttemptCorrect(attempts []string, solution string) bool {
	if len(attempts) == 0 {
		return false
	}
	return attempts[len(attempts)-1] == solution
}

func play_with_solution(solution string) {
	attempts := []string{}

	var wordlist []string
	for _, word := range allWords {
		if len(solution) != len(word) {
			continue
		}
		if word == solution {
			continue
		}
		wordlist = append(wordlist, word)
	}

	for !isAttemptCorrect(attempts, solution) {
		minNextPossibilities := len(wordlist)
		minWord := ""
		words := wordlist
		for _, word := range wordlist {
			if len(word) != len(solution) {
				continue
			}
			temp := attempts
			temp = append(temp, word)
			words = next_possible_words(temp, solution, words)
			if len(words) < minNextPossibilities {
				minNextPossibilities = len(words)
				minWord = word
			}
		}
		if len(attempts) > 0 {
			if minWord == attempts[len(attempts)-1] {
				break
			}
		}
		attempts = append(attempts, minWord)
		if minNextPossibilities == 1 {
			break
		}
	}
	attempts = append(attempts, solution)
	for i, w := range attempts {
		modify_weight(w, i)
	}
}

func remove_words(attempt, solution string, temp []string) []string {
	result := get_word_result(attempt, solution)
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
				if count_letter(word, r) != amt {
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

func next_possible_words(attempts []string, solution string, wordlist []string) []string {
	var temp []string
	for _, word := range wordlist {
		if len(solution) != len(word) {
			continue
		}
		temp = append(temp, word)
	}
	for _, attempt := range attempts {
		temp = remove_words(attempt, solution, temp)
	}
	return temp
}
