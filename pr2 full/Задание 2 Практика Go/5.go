package main

import "fmt"

func runTask5() {
	p := 23
	g := 5
	a := 6
	b := 15
	e := 9
	message := "HELLO"

	A := powerMod(g, a, p)
	B := powerMod(g, b, p)

	fakeForBob := powerMod(g, e, p)
	fakeForAlice := powerMod(g, e, p)

	keyAliceMallory := powerMod(fakeForAlice, a, p)
	keyBobMallory := powerMod(fakeForBob, b, p)
	keyMalloryWithAlice := powerMod(A, e, p)
	keyMalloryWithBob := powerMod(B, e, p)

	encryptedByAlice := encryptText(message, keyAliceMallory)
	readByMallory := decryptText(encryptedByAlice, keyMalloryWithAlice)
	changedMessage := readByMallory + "!"
	encryptedForBob := encryptText(changedMessage, keyMalloryWithBob)
	readByBob := decryptText(encryptedForBob, keyBobMallory)

	fmt.Println("\n--- Задание 5* ---")
	fmt.Println("Эмуляция атаки посередине на обмен Диффи-Хеллмана")
	fmt.Println("p =", p, ", g =", g)
	fmt.Println("Алиса отправляет A =", A, ", Боб отправляет B =", B)
	fmt.Println("Злоумышленник подменяет оба значения на E = g^e mod p =", fakeForBob)
	fmt.Println("Ключ Алиса-злоумышленник:", keyAliceMallory)
	fmt.Println("Ключ злоумышленник-Алиса:", keyMalloryWithAlice)
	fmt.Println("Ключ Боб-злоумышленник:", keyBobMallory)
	fmt.Println("Ключ злоумышленник-Боб:", keyMalloryWithBob)
	fmt.Println("Исходное сообщение Алисы:", message)
	fmt.Println("Злоумышленник прочитал:", readByMallory)
	fmt.Println("Боб получил после подмены:", readByBob)
	fmt.Println("\nКраткое сообщение по теме находится в файле 5_сообщение.txt.")

	waitEnter()
}
