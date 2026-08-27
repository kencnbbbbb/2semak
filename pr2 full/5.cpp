#include <iostream>
#include <string>

#include "func.h"

using namespace std;

void runTask5() {
    int p = 23;
    int g = 5;
    int a = 6;
    int b = 15;
    int e = 9;
    string message = "HELLO";

    int A = powerMod(g, a, p);
    int B = powerMod(g, b, p);

    int fakeForBob = powerMod(g, e, p);
    int fakeForAlice = powerMod(g, e, p);

    int keyAliceMallory = powerMod(fakeForAlice, a, p);
    int keyBobMallory = powerMod(fakeForBob, b, p);
    int keyMalloryWithAlice = powerMod(A, e, p);
    int keyMalloryWithBob = powerMod(B, e, p);

    string encryptedByAlice = encryptText(message, keyAliceMallory);
    string readByMallory = decryptText(encryptedByAlice, keyMalloryWithAlice);
    string changedMessage = readByMallory + "!";
    string encryptedForBob = encryptText(changedMessage, keyMalloryWithBob);
    string readByBob = decryptText(encryptedForBob, keyBobMallory);

    cout << "\n--- Задание 5* ---" << endl;
    cout << "Эмуляция атаки посередине на обмен Диффи-Хеллмана" << endl;
    cout << "p = " << p << ", g = " << g << endl;
    cout << "Алиса отправляет A = " << A << ", Боб отправляет B = " << B << endl;
    cout << "Злоумышленник подменяет оба значения на E = g^e mod p = " << fakeForBob << endl;
    cout << "Ключ Алиса-злоумышленник: " << keyAliceMallory << endl;
    cout << "Ключ злоумышленник-Алиса: " << keyMalloryWithAlice << endl;
    cout << "Ключ Боб-злоумышленник: " << keyBobMallory << endl;
    cout << "Ключ злоумышленник-Боб: " << keyMalloryWithBob << endl;
    cout << "Исходное сообщение Алисы: " << message << endl;
    cout << "Злоумышленник прочитал: " << readByMallory << endl;
    cout << "Боб получил после подмены: " << readByBob << endl;
    cout << "\nКраткое сообщение по теме находится в файле 5_сообщение.txt." << endl;

    waitEnter();
}
