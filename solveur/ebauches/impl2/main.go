package main

import (
	"encoding/json"
	"fmt"
	"io/ioutil"
	"strings"
)

var allWords []string

func openDict() error {
	// On ouvre juste le fichier dico là
	data, err := ioutil.ReadFile("../../dict.txt")
	if err != nil {
		return err
	}

	content := string(data)
	lines := strings.Split(content, "\n")
	allWords = append(allWords, lines...)
	return nil
}

func main() {
	openDict()
	node := btInit(5)
	node.btNextInit()

	fmt.Println(node)
	file, _ := json.MarshalIndent(node, "", " ")

	_ = ioutil.WriteFile("test.json", file, 0644)
}
