package main

import (
	"fmt"
	"sort"
	"strconv"
)

type Candidate struct {
	name  string
	score int
}

// Метод Борда
func bordaMethod(n, k int, rankings [][]int) {
	candidates := make([]Candidate, n)
	for i := 0; i < n; i++ {
		candidates[i].name = "Кандидат " + strconv.Itoa(i+1)
		candidates[i].score = 0
	}

	for i := 0; i < k; i++ {
		for j := 0; j < n; j++ {
			candidates[rankings[i][j]-1].score += (n - 1 - j)
		}
	}

	sort.Slice(candidates, func(i, j int) bool {
		return candidates[i].score > candidates[j].score
	})

	fmt.Println("Победитель по методу Борда:", candidates[0].name)
}

// Метод Кондорсе
func condorcetMethod(n, k int, rankings [][]int) {
	wins := make([][]int, n)
	for i := range wins {
		wins[i] = make([]int, n)
	}
	candidates := make([]Candidate, n)
	for i := 0; i < n; i++ {
		candidates[i].name = "Кандидат " + strconv.Itoa(i+1)
	}

	for i := 0; i < k; i++ {
		for j := 0; j < n; j++ {
			for l := j + 1; l < n; l++ {
				if rankings[i][j] < rankings[i][l] {
					wins[j][l]++
				} else {
					wins[l][j]++
				}
			}
		}
	}

	winner := -1
	for i := 0; i < n; i++ {
		isWinner := true
		for j := 0; j < n; j++ {
			if i != j && wins[i][j] <= k/2 {
				isWinner = false
				break
			}
		}
		if isWinner {
			winner = i
			break
		}
	}

	if winner != -1 {
		fmt.Println("Победитель по методу Кондерсе:", candidates[winner].name)
	} else {
		fmt.Println("Нет победителя по методу Кондерсе")
	}
}

func main() {
	var n, k int
	fmt.Print("Введите количество кандидатов (n): ")
	fmt.Scan(&n)
	fmt.Print("Введите количество голосующих (k): ")
	fmt.Scan(&k)

	rankings := make([][]int, k)
	fmt.Println("Введите рейтинги от каждого голосующего (1 = первое место, n = последнее место): ")
	for i := 0; i < k; i++ {
		rankings[i] = make([]int, n)
		for j := 0; j < n; j++ {
			fmt.Scan(&rankings[i][j])
		}
	}

	// Применение методов голосования
	bordaMethod(n, k, rankings)
	condorcetMethod(n, k, rankings)
}
