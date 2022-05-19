package main

import (
	"sync"
)

var weights map[int]map[string]int
var weightSync sync.Mutex

func init() {
	weights = make(map[int]map[string]int)
}

func modify_weight(word string, place int) {
	weightSync.Lock()
	if _, ok := weights[place]; !ok {
		weights[place] = make(map[string]int)
	}
	weights[place][word]++
	weightSync.Unlock()
}
