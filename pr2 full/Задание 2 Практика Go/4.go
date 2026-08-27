package main

import (
	"fmt"
	"strings"
)

func runTask4() {
	var p, g, a, b int

	fmt.Println("\n--- Задание 4 ---")
	fmt.Println("Диффи-Хеллман: получение общего ключа и шифрование текста")
	fmt.Print("Введите простое число p: ")
	fmt.Fscan(reader, &p)

	if !isPrime(p) {
		reader.ReadString('\n')
		fmt.Println("Ошибка: p должно быть простым.")
		waitEnter()
		return
	}

	fmt.Print("Введите основание g (1 < g < p): ")
	fmt.Fscan(reader, &g)
	if g <= 1 || g >= p {
		reader.ReadString('\n')
		fmt.Println("Ошибка: g должно быть больше 1 и меньше p.")
		waitEnter()
		return
	}

	fmt.Print("Введите секрет Алисы a: ")
	fmt.Fscan(reader, &a)
	fmt.Print("Введите секрет Боба b: ")
	fmt.Fscan(reader, &b)
	reader.ReadString('\n')

	if a <= 0 || b <= 0 {
		fmt.Println("Ошибка: секретные числа должны быть положительными.")
		waitEnter()
		return
	}

	fmt.Print("Введите исходный текст: ")
	message, _ := reader.ReadString('\n')
	message = strings.TrimRight(message, "\r\n")

	A := powerMod(g, a, p)
	B := powerMod(g, b, p)
	keyAlice := powerMod(B, a, p)
	keyBob := powerMod(A, b, p)

	fmt.Println("Открытое значение Алисы A = g^a mod p =", A)
	fmt.Println("Открытое значение Боба B = g^b mod p =", B)
	fmt.Println("Ключ Алисы:", keyAlice)
	fmt.Println("Ключ Боба:", keyBob)

	if keyAlice != keyBob {
		fmt.Println("Ошибка: ключи не совпали.")
		waitEnter()
		return
	}

	encrypted := encryptText(message, keyAlice)
	decrypted := decryptText(encrypted, keyBob)

	fmt.Println("Зашифрованный текст:", encrypted)
	fmt.Println("Расшифрованный текст:", decrypted)

	waitEnter()
}
