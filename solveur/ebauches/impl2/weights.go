package main

import (
	"sync"
)

type weights struct {
	d map[string]int
	sync.Mutex
}

func newWeights() *weights {
	return &weights{d: make(map[string]int)}
}

func (w *weights) modifyWeight(word string) {
	w.Lock()
	w.d[word]++
	w.Unlock()
}
