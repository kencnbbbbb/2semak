#include <iostream>
#include <vector>
#include <iomanip>
#include <string>

using namespace std;

// KSA — инициализация
void KSA(vector<int>& S, const vector<int>& key) {
    int j = 0;
    int key_length = key.size();

    // Заполнение S
    for (int i = 0; i < 256; ++i) {
        S[i] = i;
    }

    // Перемешивание
    for (int i = 0; i < 256; ++i) {
        j = (j + S[i] + key[i % key_length]) % 256;
        swap(S[i], S[j]);
    }
}

// PRGA — генерация
vector<int> PRGA(vector<int>& S, int n) {
    vector<int> output;
    int i = 0, j = 0;

    for (int k = 0; k < n; ++k) {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;

        swap(S[i], S[j]);

        int t = (S[i] + S[j]) % 256;
        output.push_back(S[t]);
    }

    return output;
}

int main() {
    string key_input;
    int n;

    cout << "Введите ключ: ";
    cin >> key_input;

    cout << "Сколько байтов сгенерировать: ";
    cin >> n;

    // Контейнер для ключа
    vector<int> key;
    
    // range-based for (C++11)
    for (char c : key_input) {
        key.push_back(static_cast<unsigned char>(c));
    }

    vector<int> S(256);

    // KSA
    KSA(S, key);

    // PRGA
    vector<int> keystream = PRGA(S, n);

    // Вывод с использованием range-based for
    cout << "Сгенерированная последовательность:\n";
    for (const int& byte : keystream) {
        cout << hex << setw(2) << setfill('0') << byte << " ";
    }

    cout << endl;

    return 0;
}

// вариант 1 ключ RC4