package main

import (
	"bufio"
	"fmt"
	"io"
	"os/exec"
	"syscall"

	"github.com/fatih/color"
)

// Juste pour simplifier
func startExecutable(executable string) (io.WriteCloser, *bufio.Scanner) {
	c := exec.Command("./" + executable)

	si, err := c.StdinPipe()
	if err != nil {
		panic(err)
	}
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
func runGame(executable string, n int) {
	counter := &Counters{
		Name: executable,
	}
	statCounters[executable] = counter

	for i := 0; i < n; i++ {
		stdin, stdout := startExecutable(executable)
		game, err := CreateWordle()
		if err != nil {
			panic(err)
		}
		fmt.Printf("		Starting game %d (%s) : ", i+1, game.Word)

		win, err := game.GameLoop(stdin, stdout)
		if err != nil {
			fmt.Print(color.RedString("Erreur [%s]\n", err))
		} else if win {
			fmt.Print(color.GreenString("Victoire\n"))
			counter.WinCount++
			counter.Total++
		} else {
			fmt.Print(color.RedString("Défaite\n"))
			counter.Total++
		}
		counter.UpdateAverage(len(game.Tries))
	}
	fmt.Printf("	%dW / %dL (%f)\n", counter.WinCount, counter.Total-counter.WinCount, counter.AverageTry)
	fmt.Println()
}
