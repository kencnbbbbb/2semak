package main

import "fmt"

func powerByFermat(a, x, p int) int {
	reducedDegree := x % (p - 1)
	return powerMod(a, reducedDegree, p)
}

func runTask1() {
	var a, x, p int

	fmt.Println("\n--- Задание 1 ---")
	fmt.Println("Вычисление a^x mod p")
	fmt.Print("Введите a: ")
	fmt.Fscan(reader, &a)
	fmt.Print("Введите x (x >= 0): ")
	fmt.Fscan(reader, &x)
	fmt.Print("Введите p: ")
	fmt.Fscan(reader, &p)
	reader.ReadString('\n')

	if x < 0 {
		fmt.Println("Ошибка: степень должна быть неотрицательной.")
		waitEnter()
		return
	}
	if !isPrime(p) {
		fmt.Println("Теорема Ферма неприменима: p должно быть простым числом.")
		waitEnter()
		return
	}
	if gcdSimple(a, p) != 1 {
		fmt.Println("Теорема Ферма неприменима: a и p должны быть взаимно простыми.")
		waitEnter()
		return
	}

	fmt.Println("Условия теоремы Ферма выполнены: p простое, НОД(a, p) = 1.")
	fmt.Println("По теореме Ферма: a^(p-1) сравнимо с 1 по модулю p.")
	fmt.Println("Результат через теорему Ферма:", powerByFermat(a, x, p))
	fmt.Println("Результат через двоичное разложение степени:", powerMod(a, x, p))
	fmt.Println("Контроль обычным умножением:", powerSimple(a, x, p))

	waitEnter()
}
