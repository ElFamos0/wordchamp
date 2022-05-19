package main

const (
	wrong = iota
	yellow
	green
)

func get_word_result(attempt string, solution string) []int {
	var temp []int
	var comptes = make(map[rune]int)

	for _, r := range solution {
		comptes[r] = 0
		temp = append(temp, wrong)
	}

	for i, r := range solution {
		comptes[r]++
		if attempt[i] == solution[i] {
			temp[i] = green
			comptes[r]--
		}
	}

	for i, r := range attempt {
		if temp[i] == wrong {
			if comptes[r] > 0 {
				temp[i] = yellow
				comptes[r]--
			}
		}
	}
	return temp
}
