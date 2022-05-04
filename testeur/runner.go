package main

import (
	"bufio"
	"io"
	"log"
	"os/exec"
)

// Juste pour simplifier
func startExecutable() (io.WriteCloser, *bufio.Scanner) {
	c := exec.Command(*executable)
	si, err := c.StdinPipe()
	if err != nil {
		log.Fatal(err)
	}

	so, err := c.StdoutPipe()
	if err != nil {
		log.Fatal(err)
	}
	reader := bufio.NewReader(so)
	scanner := bufio.NewScanner(reader)
	return si, scanner
}

// n is the amount of games to play
func runGame(n int) {
	stdin, stdout := startExecutable()

	for i := 0; i < n; i++ {
		game, err := CreateWordle()
		if err != nil {
			panic(err)
		}

		game.GameLoop(stdin, stdout)
	}
}
