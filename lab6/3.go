package main

import (
	"fmt"
	"math"
)

const SIZE = 4
const EPS = 1e-3

func printExtended(a [SIZE][SIZE + 1]float64) {
	for i := 0; i < SIZE; i++ {
		for j := 0; j <= SIZE; j++ {
			fmt.Printf("%12.6f", a[i][j])
		}
		fmt.Println()
	}

	fmt.Println()
}

func gauss(A [SIZE][SIZE]float64, B [SIZE]float64, x *[SIZE]float64) {
	var a [SIZE][SIZE + 1]float64

	for i := 0; i < SIZE; i++ {
		for j := 0; j < SIZE; j++ {
			a[i][j] = A[i][j]
		}

		a[i][SIZE] = B[i]
	}

	fmt.Println()
	fmt.Println("Метод Гаусса с выбором главного элемента")
	fmt.Println()
	fmt.Println("Исходная расширенная матрица:")
	printExtended(a)

	// Прямой ход
	for k := 0; k < SIZE; k++ {
		mainRow := k

		for i := k + 1; i < SIZE; i++ {
			if math.Abs(a[i][k]) > math.Abs(a[mainRow][k]) {
				mainRow = i
			}
		}

		if mainRow != k {
			for j := 0; j <= SIZE; j++ {
				a[k][j], a[mainRow][j] = a[mainRow][j], a[k][j]
			}
		}

		for i := k + 1; i < SIZE; i++ {
			m := a[i][k] / a[k][k]

			for j := k; j <= SIZE; j++ {
				a[i][j] -= m * a[k][j]
			}
		}

		fmt.Printf("Матрица после шага %d:\n", k+1)
		printExtended(a)
	}

	// Обратный ход
	for i := SIZE - 1; i >= 0; i-- {
		sum := a[i][SIZE]

		for j := i + 1; j < SIZE; j++ {
			sum -= a[i][j] * x[j]
		}

		x[i] = sum / a[i][i]
	}

	fmt.Println("Решение методом Гаусса:")

	for i := 0; i < SIZE; i++ {
		fmt.Printf("x%d = %.6f\n", i+1, x[i])
	}
}

func seidel(A [SIZE][SIZE]float64, B [SIZE]float64, x *[SIZE]float64) {
	for i := 0; i < SIZE; i++ {
		x[i] = 0
	}

	fmt.Println()
	fmt.Println("Метод Зейделя")
	fmt.Println()
	fmt.Println("Канонический вид:")
	fmt.Println("x1 = (-1.24 + 0.04*x2 - 0.21*x3 + 1.16*x4) / 0.79")
	fmt.Println("x2 = (-0.86 - 0.25*x1 - 0.18*x3 + 0.09*x4) / (-1.23)")
	fmt.Println("x3 = (2.56 + 0.21*x1 - 0.18*x2 + 0.13*x4) / 0.8")
	fmt.Println("x4 = (0.79 - 0.15*x1 + 1.31*x2 - 0.06*x3) / (-0.86)")
	fmt.Println()

	fmt.Printf("%5s%12s%12s%12s%12s%12s\n",
		"N", "x1", "x2", "x3", "x4", "eps")

	iter := 0
	errorValue := 0.0

	for {
		iter++

		var old [SIZE]float64

		for i := 0; i < SIZE; i++ {
			old[i] = x[i]
		}

		for i := 0; i < SIZE; i++ {
			sum := B[i]

			for j := 0; j < SIZE; j++ {
				if i != j {
					sum -= A[i][j] * x[j]
				}
			}

			x[i] = sum / A[i][i]
		}

		errorValue = math.Abs(x[0] - old[0])

		for i := 1; i < SIZE; i++ {
			currentError := math.Abs(x[i] - old[i])

			if currentError > errorValue {
				errorValue = currentError
			}
		}

		fmt.Printf("%5d%12.6f%12.6f%12.6f%12.6f%12.6f\n",
			iter, x[0], x[1], x[2], x[3], errorValue)

		if errorValue <= EPS {
			break
		}
	}

	fmt.Println()
	fmt.Println("Решение методом Зейделя:")

	for i := 0; i < SIZE; i++ {
		fmt.Printf("x%d = %.6f\n", i+1, x[i])
	}
}

func main() {
	M := 0.79
	K := 0.18
	P := -0.86

	A := [SIZE][SIZE]float64{
		{M, -0.04, 0.21, -1.16},
		{0.25, -1.23, K, -0.09},
		{-0.21, K, 0.8, -0.13},
		{0.15, -1.31, 0.06, P},
	}

	B := [SIZE]float64{
		-1.24,
		P,
		2.56,
		M,
	}

	var xGauss [SIZE]float64
	var xSeidel [SIZE]float64

	fmt.Println("Вариант 6")
	fmt.Printf("M = %.2f, N = %.2f, P = %.2f\n", M, K, P)

	gauss(A, B, &xGauss)
	seidel(A, B, &xSeidel)

	fmt.Println()
	fmt.Println("Итоговый ответ:")

	for i := 0; i < SIZE; i++ {
		fmt.Printf("x%d = %.6f\n", i+1, xGauss[i])
	}
}