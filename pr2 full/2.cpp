#include <iostream>

#include "func.h"

using namespace std;

void runTask2() {
    int c, m;

    cout << "\n--- Задание 2 ---" << endl;
    cout << "Решение сравнения c * d mod m = 1 через u и v" << endl;
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

    cout << "Расширенный алгоритм Евклида:" << endl;
    cout << m << " * " << r.u << " + " << c << " * " << r.v << " = " << r.d << endl;

    if (r.d != 1) {
        cout << "Решения нет, так как НОД(c, m) != 1." << endl;
        waitEnter();
        return;
    }

    int d = positiveMod(r.v, m);
    cout << "Из равенства m*u + c*v = 1 получаем d = v mod m." << endl;
    cout << "d = " << d << endl;
    cout << "Проверка: (c * d) mod m = " << positiveMod(c * d, m) << endl;

    waitEnter();
}
