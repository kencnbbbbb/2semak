#include <iostream>

#include "func.h"

using namespace std;

int powerByFermat(int a, int x, int p) {
    int reducedDegree = x % (p - 1);
    return powerMod(a, reducedDegree, p);
}

void runTask1() {
    int a, x, p;

    cout << "\n--- Задание 1 ---" << endl;
    cout << "Вычисление a^x mod p" << endl;
    cout << "Введите a: ";
    cin >> a;
    cout << "Введите x (x >= 0): ";
    cin >> x;
    cout << "Введите p: ";
    cin >> p;

    if (x < 0) {
        cout << "Ошибка: степень должна быть неотрицательной." << endl;
        waitEnter();
        return;
    }

    if (!isPrime(p)) {
        cout << "Теорема Ферма неприменима: p должно быть простым числом." << endl;
        waitEnter();
        return;
    }

    if (gcdSimple(a, p) != 1) {
        cout << "Теорема Ферма неприменима: a и p должны быть взаимно простыми." << endl;
        waitEnter();
        return;
    }

    cout << "Условия теоремы Ферма выполнены: p простое, НОД(a, p) = 1." << endl;
    cout << "По теореме Ферма: a^(p-1) сравнимо с 1 по модулю p." << endl;
    cout << "Результат через теорему Ферма: " << powerByFermat(a, x, p) << endl;
    cout << "Результат через двоичное разложение степени: " << powerMod(a, x, p) << endl;
    cout << "Контроль обычным умножением: " << powerSimple(a, x, p) << endl;

    waitEnter();
}
