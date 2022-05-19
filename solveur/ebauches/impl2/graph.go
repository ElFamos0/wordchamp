package main

import (
	"sync"

	progressBar "github.com/schollz/progressbar/v3"
)

type node struct {
	Word string           `json:"word"`
	Next map[string]*node `json:"next"`

	Length   *int     `json:"-"`
	State    []string `json:"-"`
	Results  [][]int  `json:"-"`
	Wordlist []string `json:"-"`

	sync.Mutex
}

type letter struct {
	Rune     rune
	Amount   int
	CannotBe []int
	MustBe   []int
}

func (n *node) initNext(result []int) *node {
	r := n.Results
	r = append(r, result)
	str := resultToString(result...)
	node := &node{
		Next:     make(map[string]*node),
		Results:  r,
		Wordlist: nextWordList(n.State, r, n.Wordlist),
	}
	go func() {
		n.Lock()
		n.Next[str] = node
		n.Unlock()
	}()
	return node
}

func btInit(length int) *node {
	// We compute the first word only

	var words []string
	for _, word := range allWords {
		if len(word) != length {
			continue
		}
		words = append(words, word)
	}

	weight := newWeights()
	wg := sync.WaitGroup{}
	node := &node{
		Next:     make(map[string]*node),
		Wordlist: words,
	}
	bar := progressBar.New(len(words))
	for i, solution := range words {
		wg.Add(1)
		go func(s string) {
			node.pass(s, weight)
			bar.Add(1)
			wg.Done()
		}(solution)
		if i == 1000 {
			break
		}
	}
	wg.Wait()
	bar.Clear()
	// Find word with max weight
	max := 0
	maxS := ""
	for s, w := range weight.d {
		if w > max {
			max = w
			maxS = s
		}
	}

	node.Word = maxS
	node.State = []string{maxS}
	return node
}

func (n *node) btNextInit() {
	words := n.Wordlist
	bar := progressBar.New(len(words))
	for i, solution := range words {
		result := getWordResult(n.Word, solution)
		next := n.initNext(result)
		next.passBt()
		bar.Add(1)
		if i == 2 {
			break
		}
	}
	bar.Clear()
}

func (n *node) passBt() {
	weight := newWeights()
	wg := sync.WaitGroup{}
	node := &node{
		Next:     make(map[string]*node),
		Wordlist: n.Wordlist,
	}
	for _, solution := range n.Wordlist {
		wg.Add(1)
		go func(s string) {
			node.pass(s, weight)
			wg.Done()
		}(solution)
	}
	wg.Wait()
	// Find word with max weight
	max := 0
	maxS := ""
	for s, w := range weight.d {
		if w > max {
			max = w
			maxS = s
		}
	}

	node.Word = maxS
	node.State = []string{maxS}
}

func (n *node) pass(solution string, weight *weights, attempts ...string) {
	wordlist := n.Wordlist
	minNextPossibilities := len(wordlist)
	minWord := ""
	for _, word := range wordlist {
		if word == solution {
			continue
		}
		t := attempts
		t = append(t, word)
		amt := countNextPossibles(solution, wordlist, minNextPossibilities, t...)
		if amt < minNextPossibilities {
			minNextPossibilities = amt
			minWord = word
		}
		if minNextPossibilities == 1 {
			break
		}
	}

	weight.modifyWeight(minWord)
	return
}
