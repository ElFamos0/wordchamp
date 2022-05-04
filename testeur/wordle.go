package main

import (
	"bufio"
	"errors"
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
		return nil, err
	}

	word := wordleDictionary[rand.Intn(len(wordleDictionary))]

	return &Wordle{
		Word:  word,
		Tries: []string{},

		MaxTry: len(word),
	}, nil
}

func (w *Wordle) InputWord(guess string) (result string, err error) {
	// On vérifie que le guess est bien de la bonne taille
	if len(guess) != len(w.Word) {
		return "", errors.New("wrong guess size")
	}

	// On met le guess en majuscule pour éviter les erreurs
	guess = strings.ToUpper(guess)

	var temp []rune
	var comptes = make(map[rune]int)

	// On initialise result a 000..00
	for _, r := range guess {
		comptes[r] = 0
		temp = append(temp, wrong)
	}

	// i vaut l'index en cours
	// r correspond au caractère en cours (appelé rune)
	for i, r := range guess {
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
	if len(w.Tries) >= w.MaxTry {
		return true, false
	} else if w.Tries[len(w.Tries)-1] == w.Word {
		return true, true
	}
	return false, false
}

func (w *Wordle) GameLoop(stdin io.WriteCloser, stdout *bufio.Scanner) (win bool) {
	for finished, _ := w.IsFinished(); finished; {
		stdout.Scan() // On attend une réponse
		input := stdout.Text()
		result, err := w.InputWord(input)
		if err != nil {
			panic(err)
		}
		w.Tries = append(w.Tries, result)
		stdin.Write([]byte(result + "\n"))
	}
	_, win = w.IsFinished()
	return win
}
