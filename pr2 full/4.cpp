#include <iostream>
#include <string>

#include "func.h"

using namespace std;

void runTask4() {
    int p, g, a, b;
    string message;

    cout << "\n--- Задание 4 ---" << endl;
    cout << "Диффи-Хеллман: получение общего ключа и шифрование текста" << endl;
    cout << "Введите простое число p: ";
    cin >> p;

    if (!isPrime(p)) {
        cout << "Ошибка: p должно быть простым." << endl;
        waitEnter();
        return;
    }

    cout << "Введите основание g (1 < g < p): ";
    cin >> g;
    if (g <= 1 || g >= p) {
        cout << "Ошибка: g должно быть больше 1 и меньше p." << endl;
        waitEnter();
        return;
    }

    cout << "Введите секрет Алисы a: ";
    cin >> a;
    cout << "Введите секрет Боба b: ";
    cin >> b;

    if (a <= 0 || b <= 0) {
        cout << "Ошибка: секретные числа должны быть положительными." << endl;
        waitEnter();
        return;
    }

    cin.ignore();
    cout << "Введите исходный текст: ";
    getline(cin, message);

    int A = powerMod(g, a, p);
    int B = powerMod(g, b, p);
    int keyAlice = powerMod(B, a, p);
    int keyBob = powerMod(A, b, p);

    cout << "Открытое значение Алисы A = g^a mod p = " << A << endl;
    cout << "Открытое значение Боба B = g^b mod p = " << B << endl;
    cout << "Ключ Алисы: " << keyAlice << endl;
    cout << "Ключ Боба: " << keyBob << endl;

    if (keyAlice != keyBob) {
        cout << "Ошибка: ключи не совпали." << endl;
        waitEnter();
        return;
    }

    string encrypted = encryptText(message, keyAlice);
    string decrypted = decryptText(encrypted, keyBob);

    cout << "Зашифрованный текст: " << encrypted << endl;
    cout << "Расшифрованный текст: " << decrypted << endl;

    waitEnter();
}
