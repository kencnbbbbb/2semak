#include <iostream>
#include <limits>

#include "func.h"

using namespace std;

int main() {
    int choice;

    do {
        cout << "\n=== Практика 2. Меню заданий ===" << endl;
        cout << "1. a^x mod p: теорема Ферма и двоичный алгоритм" << endl;
        cout << "2. Расширенный алгоритм Евклида: c * d mod m = 1" << endl;
        cout << "3. Взаимно обратное число c^(-1) mod m" << endl;
        cout << "4. Диффи-Хеллман и шифрование текста" << endl;
        cout << "5. Атака посередине" << endl;
        cout << "6. Цепная дробь и уравнение 143a + 169b = 5" << endl;
        cout << "0. Выход" << endl;
        cout << "Выберите задание: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка ввода. Нужно ввести номер пункта." << endl;
            continue;
        }

        switch (choice) {
            case 1: runTask1(); break;
            case 2: runTask2(); break;
            case 3: runTask3(); break;
            case 4: runTask4(); break;
            case 5: runTask5(); break;
            case 6: runTask6(); break;
            case 0: cout << "Выход из программы." << endl; break;
            default: cout << "Такого пункта нет." << endl;
        }
    } while (choice != 0);

    return 0;
}
