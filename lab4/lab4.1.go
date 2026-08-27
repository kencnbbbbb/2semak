package main

import (
    "fmt"
    "math"
)

const (
    EPS      = 1e-4
    MAX_ITER = 100
)

type Iteration struct {
    n    int
    xn   float64
    xn1  float64
    diff float64
}

// функция
func f(x float64) float64 {
    return x*x - 3*math.Sin(x)
}

// производная
func df(x float64) float64 {
    return 2*x - 3*math.Cos(x)
}

// для итераций
func g(x float64) float64 {
    return math.Sqrt(3 * math.Sin(x))
}

// --- Метод Ньютона ---
func newton(x0 float64) []Iteration {
    var table []Iteration
    x := x0
    for n := 0; n < MAX_ITER; n++ {
        x1 := x - f(x)/df(x)
        diff := math.Abs(x1 - x)
        table = append(table, Iteration{n, x, x1, diff})
        if diff < EPS {
            break
        }
        x = x1
    }
    return table
}

// --- Метод бисекции ---
func bisection(a, b float64) []Iteration {
    var table []Iteration
    for n := 0; n < MAX_ITER; n++ {
        c := (a + b) / 2.0
        diff := math.Abs(b - a)
        table = append(table, Iteration{n, a, b, diff})
        if diff < EPS {
            break
        }
        if f(a)*f(c) < 0 {
            b = c
        } else {
            a = c
        }
    }
    return table
}

// --- Метод простых итераций ---
func simpleIteration(x0 float64) []Iteration {
    var table []Iteration
    x := x0
    for n := 0; n < MAX_ITER; n++ {
        if math.Sin(x) < 0 {
            break // защита
        }
        x1 := g(x)
        diff := math.Abs(x1 - x)
        table = append(table, Iteration{n, x, x1, diff})
        if diff < EPS {
            break
        }
        x = x1
    }
    return table
}

// --- Вывод таблицы ---
func printTable(table []Iteration) {
    fmt.Printf("N\txn\t\txn+1\t\tdelta\n")
    for _, row := range table {
        fmt.Printf("%d\t%.6f\t%.6f\t%.6f\n", row.n, row.xn, row.xn1, row.diff)
    }
    if len(table) > 0 {
        fmt.Printf("Корень ≈ %.6f\n", table[len(table)-1].xn1)
    }
}

func main() {
    fmt.Printf("\n=== Корень на [1,2] ===\n")

    fmt.Printf("\nМетод бисекции:\n")
    bis := bisection(1, 2)
    printTable(bis)

    fmt.Printf("\nМетод Ньютона:\n")
    newt := newton(1.5)
    printTable(newt)

    fmt.Printf("\nМетод простых итераций:\n")
    iter := simpleIteration(1.5)
    printTable(iter)
}