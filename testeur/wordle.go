package main

import (
	"bufio"
	"fmt"
	"io"
	"math/rand"
	"strings"
)

// On crée la partie pour simplifier les appels de fonctions etc (c'est un peu de la POO)
type Wordle struct {
	Word  string
	Tries []string

	// Nombre maximum d'essais (on va prendre len(Word) mais ca peut changer)
	MaxTry int
}

const (
	wrong  = '0'
	yellow = '1'
	green  = '2'
)

func CreateWordle() (*Wordle, error) {
	if len(wordleDictionary) == 0 {
		err := openDict()
		if err != nil {
			return nil, err
		}
	}

	if *word != "default" {
		*word = strings.ToUpper(*word)
		return &Wordle{
			Word:  *word,
			Tries: []string{},

			MaxTry: len(*word),
		}, nil
	}

	word := wordleDictionary[rand.Intn(len(wordleDictionary))]
	word = strings.ToUpper(word)
	return &Wordle{
		Word:  word,
		Tries: []string{},

		MaxTry: len(word),
	}, nil
}

func (w *Wordle) InputWord(guess string) (result string, err error) {
	// On vérifie que le guess est bien de la bonne taille
	if len(guess) != len(w.Word) {
		return "", fmt.Errorf("wrong guess size (%s)", guess)
	}

	// On met le guess en majuscule pour éviter les erreurs
	guess = strings.ToUpper(guess)

	var temp []rune
	var comptes = make(map[rune]int)

	// On initialise result a 000..00
	for _, r := range w.Word {
		comptes[r] = 0
		temp = append(temp, wrong)
	}

	// i vaut l'index en cours
	// r correspond au caractère en cours (appelé rune)
	for i, r := range w.Word {
		comptes[r]++
		if guess[i] == w.Word[i] {
			// On a trouvé un charactere
			temp[i] = green
			comptes[r]--
		}
	}

	// i vaut toujours l'index en cours
	for i, r := range guess {
		if temp[i] == wrong {
			if comptes[r] > 0 {
				temp[i] = yellow
				comptes[r]--
			}
		}
	}

	return string(temp), nil
}

func (w *Wordle) IsFinished() (finished bool, win bool) {
	if len(w.Tries) > 0 {
		if w.Tries[len(w.Tries)-1] == w.Word {
			return true, true
		} else if len(w.Tries) >= w.MaxTry {
			return true, false
		}
	}
	return false, false
}

func (w *Wordle) GameLoop(stdin io.WriteCloser, stdout *bufio.Scanner) (win bool, err error) {
	for finished, _ := w.IsFinished(); !finished; {
		stdout.Scan() // On attend une réponse
		input := stdout.Text()
		input = strings.ToUpper(input)
		result, err := w.InputWord(input)
		if err != nil {
			return false, err
		}
		w.Tries = append(w.Tries, input)
		stdin.Write([]byte(result + "\n"))

		finished, _ = w.IsFinished()
		if finished {
			break
		}
	}
	_, win = w.IsFinished()
	return win, nil
}

func (w *Wordle) PrintGame() {
	fmt.Println("-------", w.Word, "-------")
	fmt.Println("Tries :")
	for _, try := range w.Tries {
		fmt.Printf("   > {%s}\n", try)
		r, _ := w.InputWord(try)
		fmt.Printf("   < %s\n", r)
	}
	fmt.Print("Etat : ")
	_, win := w.IsFinished()
	if win {
		fmt.Print("Victoire\n")
	} else {
		fmt.Print("Défaite\n")
	}
	fmt.Println("---------------------")
}
