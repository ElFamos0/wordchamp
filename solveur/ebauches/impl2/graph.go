package main

type node struct {
	word string
	next map[string]*node
}
