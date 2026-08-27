package main

import "fmt"

func runTask2() {
	var c, m int

	fmt.Println("\n--- Задание 2 ---")
	fmt.Println("Решение сравнения c * d mod m = 1 через u и v")
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
	fmt.Println("Расширенный алгоритм Евклида:")
	fmt.Printf("%d * %d + %d * %d = %d\n", m, r.U, c, r.V, r.D)

	if r.D != 1 {
		fmt.Println("Решения нет, так как НОД(c, m) != 1.")
		waitEnter()
		return
	}

	d := positiveMod(r.V, m)
	fmt.Println("Из равенства m*u + c*v = 1 получаем d = v mod m.")
	fmt.Println("d =", d)
	fmt.Println("Проверка: (c * d) mod m =", positiveMod(c*d, m))

	waitEnter()
}
