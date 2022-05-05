package main

import (
	"flag"
	"log"
	"os"
)

var (
	// Valeur qui stockera le nom du fichier à tester
	executable = flag.String("executable", "wordchamp_solver", "path to the executable to run")

	// Valeur qui stockera le nom du dictionnaire à ouvrir
	dictionary = flag.String("dictionary", "dict.txt", "path to the dictionary to use")

	// Valeur de la solution (DEBUG)
	word = flag.String("word", "default", "[debug] word to put as a solution")

	// Valeur qui stockera le nombre de lettre dans le mot
	size = flag.Int("size", 5, "size of the word to find")

	// Valeur qui stockera le nombre de lettre dans le mot
	games = flag.Int("games", 1, "how many games to play")
)

func main() {
	// On récupére depuis l'appel du programme la valeur de l'argument -executable
	// Exemple : testeur -executable=wordchamp_solver
	flag.Parse()

	// On vérifie que le fichier executable existe bien
	_, err := os.Stat(*executable)
	if err != nil {
		// Il existe pas là donc on panique
		panic(err)
	}
	log.Println("Executable found")

	// On vérifie que le fichier du dictionnaire existe bien
	_, err = os.Stat(*dictionary)
	if err != nil {
		// Il existe pas là donc on panique
		panic(err)
	}
	log.Println("Dictionary found")

	sz, err := readSize()
	if err != nil {
		// Il existe pas là donc on panique
		panic(err)
	}
	size = &sz
	log.Println("Size found")

	runGame(*games)
}
