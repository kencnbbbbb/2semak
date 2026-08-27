package main

import "fmt"

func runTask3() {
	var c, m int

	fmt.Println("\n--- Задание 3 ---")
	fmt.Println("Вычисление взаимно обратного числа c^(-1) mod m = d")
	fmt.Print("Введите c: ")
	fmt.Fscan(reader, &c)
	fmt.Print("Введите m: ")
	fmt.Fscan(reader, &m)
	reader.ReadString('\n')

	if m <= 1 {
		fmt.Println("Ошибка: модуль m должен быть больше 1.")
		waitEnter()
		return
	}

	r := extendedEuclid(m, c)
	fmt.Printf("Получено: %d * %d + %d * %d = %d\n", m, r.U, c, r.V, r.D)

	if r.D != 1 {
		fmt.Println("Обратного числа не существует, так как НОД(c, m) != 1.")
		waitEnter()
		return
	}

	d := positiveMod(r.V, m)
	fmt.Println("c^(-1) mod m =", d)
	fmt.Println("Проверка: (c * d) mod m =", positiveMod(c*d, m))

	waitEnter()
}
