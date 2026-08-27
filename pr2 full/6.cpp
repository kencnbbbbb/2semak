#include <iostream>

#include "func.h"

using namespace std;

void printContinuedFraction(int numerator, int denominator) {
    cout << numerator << "/" << denominator << " = [";

    int a = numerator;
    int b = denominator;
    bool first = true;

    while (b != 0) {
        int q = a / b;
        int r = a % b;

        if (!first) cout << "; ";
        cout << q;
        first = false;

        a = b;
        b = r;
    }

    cout << "]" << endl;
}

void runTask6() {
    int A = 143;
    int B = 169;
    int D = 5;

    cout << "\n--- Задание 6 ---" << endl;
    cout << "Цепная дробь для отношения коэффициентов:" << endl;
    printContinuedFraction(A, B);

    EuclidResult r = extendedEuclid(A, B);
    cout << "Расширенный алгоритм Евклида:" << endl;
    cout << A << " * " << r.u << " + " << B << " * " << r.v << " = " << r.d << endl;

    if (D % r.d != 0) {
        cout << "Уравнение " << A << "a + " << B << "b = " << D << " не имеет целых решений." << endl;
        waitEnter();
        return;
    }

    int multiplier = D / r.d;
    int a0 = r.u * multiplier;
    int b0 = r.v * multiplier;

    cout << "Частное целое решение:" << endl;
    cout << "a = " << a0 << ", b = " << b0 << endl;
    cout << "Проверка: " << A << " * " << a0 << " + " << B << " * " << b0 << " = " << A * a0 + B * b0 << endl;

    cout << "Общее решение:" << endl;
    cout << "a = " << a0 << " + " << B / r.d << " * t" << endl;
    cout << "b = " << b0 << " - " << A / r.d << " * t" << endl;
    cout << "где t — любое целое число." << endl;

    waitEnter();
}
