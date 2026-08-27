package main

import (
	"bufio"
	"fmt"
	"os"
)

type EuclidResult struct {
	D int
	U int
	V int
}

var reader = bufio.NewReader(os.Stdin)

func positiveMod(value, mod int) int {
	r := value % mod
	if r < 0 {
		r += mod
	}
	return r
}

func abs(value int) int {
	if value < 0 {
		return -value
	}
	return value
}

func isPrime(n int) bool {
	if n < 2 {
		return false
	}
	if n == 2 {
		return true
	}
	if n%2 == 0 {
		return false
	}
	for d := 3; d*d <= n; d += 2 {
		if n%d == 0 {
			return false
		}
	}
	return true
}

func gcdSimple(a, b int) int {
	a = abs(a)
	b = abs(b)
	for b != 0 {
		r := a % b
		a = b
		b = r
	}
	return a
}

func multiplyMod(a, b, mod int) int {
	return positiveMod(positiveMod(a, mod)*positiveMod(b, mod), mod)
}

func powerSimple(a, x, p int) int {
	result := 1 % p
	base := positiveMod(a, p)
	for i := 0; i < x; i++ {
		result = multiplyMod(result, base, p)
	}
	return result
}

func powerMod(a, x, p int) int {
	result := 1 % p
	base := positiveMod(a, p)
	for x > 0 {
		if x%2 == 1 {
			result = multiplyMod(result, base, p)
		}
		base = multiplyMod(base, base, p)
		x /= 2
	}
	return result
}

func extendedEuclid(a, b int) EuclidResult {
	x1, x2, x3 := abs(a), 1, 0
	y1, y2, y3 := abs(b), 0, 1

	for y1 != 0 {
		q := x1 / y1
		t1 := x1 - q*y1
		t2 := x2 - q*y2
		t3 := x3 - q*y3

		x1, x2, x3 = y1, y2, y3
		y1, y2, y3 = t1, t2, t3
	}

	if a < 0 {
		x2 = -x2
	}
	if b < 0 {
		x3 = -x3
	}

	return EuclidResult{D: x1, U: x2, V: x3}
}

func encryptText(text string, key int) string {
	data := []byte(text)
	shift := byte(key % 256)
	for i := 0; i < len(data); i++ {
		data[i] += shift
	}
	return string(data)
}

func decryptText(text string, key int) string {
	data := []byte(text)
	shift := byte(key % 256)
	for i := 0; i < len(data); i++ {
		data[i] -= shift
	}
	return string(data)
}

func waitEnter() {
	fmt.Print("\nНажмите Enter для возврата в меню...")
	reader.ReadString('\n')
}
