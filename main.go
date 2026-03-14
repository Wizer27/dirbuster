package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"flag"
)

func main() {
	file, err := os.Open("dirs.txt")

	if err != nil {
		log.Fatal(err)
	}

	defer file.Close()

	scanner := bufio.NewScanner(file)

	for scanner.Scan() {
		line := scanner.Text()
		fmt.Println(line)
	}

	if err := scanner.Err(); err != nil {
		log.Fatal(err)
	}
}
