package main

import (
	"bufio"
	"fmt"
	"io"
	"os/exec"
	"strings"
	"syscall"

	"log"
)

// Juste pour simplifier
func startExecutable() (io.WriteCloser, *bufio.Scanner) {
	c := exec.Command("./" + *executable)

	si, err := c.StdinPipe()
	if err != nil {
		panic(err)
	}
	log.Println("Got STDIN pipe")
	c.SysProcAttr = &syscall.SysProcAttr{
		Pdeathsig: syscall.SIGKILL,
	}

	so, err := c.StdoutPipe()
	if err != nil {
		panic(err)
	}

	c.Start()

	scanner := bufio.NewScanner(so)

	return si, scanner
}

// n is the amount of games to play
func runGame(n int) {
	for i := 0; i < n; i++ {
		stdin, stdout := startExecutable()
		game, err := CreateWordle()
		if err != nil {
			panic(err)
		}
		log.Printf("Starting game %d\n", i)

		game.GameLoop(stdin, stdout)
	}
}

func RunCommandCh(stdoutCh chan<- string, cutset string, command string, flags ...string) error {
	cmd := exec.Command(command, flags...)

	output, err := cmd.StdoutPipe()
	if err != nil {
		return fmt.Errorf("RunCommand: cmd.StdoutPipe(): %v", err)
	}

	if err := cmd.Start(); err != nil {
		return fmt.Errorf("RunCommand: cmd.Start(): %v", err)
	}

	scanner := bufio.NewScanner(output)
	go func() {
		defer close(stdoutCh)
		for scanner.Scan() {
			text := scanner.Text()
			for {
				// Take the index of any of the given cutset
				n := strings.IndexAny(text, cutset)
				if n == -1 {
					// If not found, but still have data, send it
					if len(text) > 0 {
						stdoutCh <- text
					}
					break
				}
				// Send data up to the found cutset
				stdoutCh <- text[:n]
				// If cutset is last element, stop there.
				if n == len(text) {
					break
				}
				// Shift the text and start again.
				text = text[n+1:]
			}
		}
	}()

	if err := scanner.Err(); err != nil {
		log.Printf("RunCommand: scan process output error: %s", err)
	}

	if err := cmd.Wait(); err != nil {
		return fmt.Errorf("RunCommand: cmd.Wait(): %v", err)
	}

	return nil
}
