package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strconv"
)

func main() {
	if len(os.Args) < 1 {
		fmt.Println("Input file expected")
		log.Fatal()
	}

	file, err := os.Open(os.Args[1])
	if err != nil {
		log.Fatal(err)
	}
	defer file.Close()

	// equivalent var costs []int
	costs := []int64{}
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		x, _ := strconv.ParseInt(scanner.Text(), 10, 64)
		costs = append(costs, x)
		for i := range costs {
			if costs[i] == 2020 - x {
				fmt.Printf("Found! %d + %d = %d\n", x, costs[i], x + costs[i])
				fmt.Printf("Result is %d\n", x * costs[i])
				os.Exit(0)
			}
		}

	}

	if err := scanner.Err(); err != nil {
		log.Fatal(err)
	}
}
