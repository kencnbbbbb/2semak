package main

import (
	"bufio"
	"fmt"
	"os"
)

var N, M int
var variantNumber int

func getIndex(i, j int) int {
	return i*M + j
}

func boardToMask(board [][]int) int64 {
	var mask int64 = 0

	for i := 0; i < N; i++ {
		for j := 0; j < M; j++ {
			if board[i][j] == 1 {
				pos := getIndex(i, j)
				mask |= 1 << pos
			}
		}
	}

	return mask
}

func makeTargetMask(firstValue int) int64 {
	var mask int64 = 0

	for i := 0; i < N; i++ {
		for j := 0; j < M; j++ {
			value := 0

			if variantNumber == 1 {
				// Шахматный порядок
				if (i+j)%2 == 0 {
					value = firstValue
				} else {
					value = 1 - firstValue
				}
			} else if variantNumber == 2 {
				// Рамка
				border := i == 0 || i == N-1 || j == 0 || j == M-1

				if border {
					value = firstValue
				} else {
					value = 1 - firstValue
				}
			} else if variantNumber == 3 {
				// Верхняя и нижняя половины
				upperHalf := i < N/2

				if upperHalf {
					value = firstValue
				} else {
					value = 1 - firstValue
				}
			}

			if value == 1 {
				pos := getIndex(i, j)
				mask |= 1 << pos
			}
		}
	}

	return mask
}

func makeMoves() []int64 {
	moves := make([]int64, 0)

	for i := 0; i < N; i++ {
		for j := 0; j < M; j++ {
			current := getIndex(i, j)

			// Сосед справа
			if j+1 < M {
				right := getIndex(i, j+1)
				moveMask := int64(1<<current) | int64(1<<right)
				moves = append(moves, moveMask)
			}

			// Сосед снизу
			if i+1 < N {
				down := getIndex(i+1, j)
				moveMask := int64(1<<current) | int64(1<<down)
				moves = append(moves, moveMask)
			}
		}
	}

	return moves
}

func bfs(startMask int64, targetMask int64, moves []int64) int {
	if startMask == targetMask {
		return 0
	}

	queue := make([]int64, 0)
	distance := make(map[int64]int)

	queue = append(queue, startMask)
	distance[startMask] = 0

	for len(queue) > 0 {
		currentMask := queue[0]
		queue = queue[1:]

		currentDistance := distance[currentMask]

		for _, moveMask := range moves {
			nextMask := currentMask ^ moveMask

			if _, exists := distance[nextMask]; !exists {
				distance[nextMask] = currentDistance + 1

				if nextMask == targetMask {
					return currentDistance + 1
				}

				queue = append(queue, nextMask)
			}
		}
	}

	return -1
}

func main() {
	reader := bufio.NewReader(os.Stdin)

	fmt.Print("Введите N и M: ")
	fmt.Fscan(reader, &N, &M)

	if N*M > 25 {
		fmt.Println("Ошибка: для данного способа решения размер доски должен быть не больше 25 клеток.")
		return
	}

	fmt.Print("Введите номер варианта (1, 2 или 3): ")
	fmt.Fscan(reader, &variantNumber)

	if variantNumber < 1 || variantNumber > 3 {
		fmt.Println("Ошибка: номер варианта должен быть 1, 2 или 3.")
		return
	}

	board := make([][]int, N)

	fmt.Println("Введите доску из 0 и 1:")

	for i := 0; i < N; i++ {
		board[i] = make([]int, M)

		for j := 0; j < M; j++ {
			fmt.Fscan(reader, &board[i][j])

			if board[i][j] != 0 && board[i][j] != 1 {
				fmt.Println("Ошибка: элементы доски должны быть только 0 или 1.")
				return
			}
		}
	}

	startMask := boardToMask(board)

	moves := makeMoves()

	target1 := makeTargetMask(0)
	target2 := makeTargetMask(1)

	result1 := bfs(startMask, target1, moves)
	result2 := bfs(startMask, target2, moves)

	answer := -1

	if result1 == -1 && result2 == -1 {
		answer = -1
	} else if result1 == -1 {
		answer = result2
	} else if result2 == -1 {
		answer = result1
	} else {
		if result1 < result2 {
			answer = result1
		} else {
			answer = result2
		}
	}

	if answer == -1 {
		fmt.Println("Невозможно получить нужный рисунок.")
	} else {
		fmt.Println("Минимальное количество ходов:", answer)
	}
}