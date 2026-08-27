package main

import "fmt"

func main() {
	for {
		var choice int

		fmt.Println("\n=== Практика 2. Меню заданий Go ===")
		fmt.Println("1. a^x mod p: теорема Ферма и двоичный алгоритм")
		fmt.Println("2. Расширенный алгоритм Евклида: c * d mod m = 1")
		fmt.Println("3. Взаимно обратное число c^(-1) mod m")
		fmt.Println("4. Диффи-Хеллман и шифрование текста")
		fmt.Println("5. Атака посередине")
		fmt.Println("0. Выход")
		fmt.Print("Выберите задание: ")

		if _, err := fmt.Fscan(reader, &choice); err != nil {
			fmt.Println("Ввод завершён. Выход из программы.")
			return
		}
		reader.ReadString('\n')

		switch choice {
		case 1:
			runTask1()
		case 2:
			runTask2()
		case 3:
			runTask3()
		case 4:
			runTask4()
		case 5:
			runTask5()
		case 0:
			fmt.Println("Выход из программы.")
			return
		default:
			fmt.Println("Такого пункта нет.")
		}
	}
}
