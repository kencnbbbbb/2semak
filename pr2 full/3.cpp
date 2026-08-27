#include <iostream>

#include "func.h"

using namespace std;

void runTask3() {
    int c, m;

    cout << "\n--- Задание 3 ---" << endl;
    cout << "Вычисление взаимно обратного числа c^(-1) mod m = d" << endl;
    cout << "Введите c: ";
    cin >> c;
    cout << "Введите m: ";
    cin >> m;

    if (m <= 1) {
        cout << "Ошибка: модуль m должен быть больше 1." << endl;
        waitEnter();
        return;
    }

    EuclidResult r = extendedEuclid(m, c);

    cout << "Получено: " << m << " * " << r.u << " + " << c << " * " << r.v << " = " << r.d << endl;

    if (r.d != 1) {
        cout << "Обратного числа не существует, так как НОД(c, m) != 1." << endl;
        waitEnter();
        return;
    }

    int d = positiveMod(r.v, m);
    cout << "c^(-1) mod m = " << d << endl;
    cout << "Проверка: (c * d) mod m = " << positiveMod(c * d, m) << endl;

    waitEnter();
}
