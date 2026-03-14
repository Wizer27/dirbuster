package main

import (
	"bufio"
	"flag"
	"fmt"
	"log"
	"net/http"
	"os"
	"strconv"
)

func main() {
	filename := flag.String("f", "", "File with dirs")

	url := flag.String("u", "", "Url to attack")

	flag.Parse()

	file, err := os.Open(*filename)

	if err != nil {
		log.Fatal(err)
	}

	defer file.Close()

	scanner := bufio.NewScanner(file)

	for scanner.Scan() {
		line := scanner.Text()
		test_ur := *url + line
		resp, err := http.Get(test_ur)
		if err != nil {
			log.Fatal(err)
		}

		if resp.StatusCode != 404 {
			status_code_str := strconv.Itoa(resp.StatusCode) 
			fmt.Println("[+] " + test_ur)
			fmt.Println("[+] Status code " + status_code_str)
		}
		defer resp.Body.Close()

	}

	if err := scanner.Err(); err != nil {
		log.Fatal(err)
	}
}
