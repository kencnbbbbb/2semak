// mt19937
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
    int n;
    cout << "Введите размер массива (n >= 10): ";
    cin >> n;

    if (n < 10) {
        cout << "Ошибка: n должно быть >= 10\n";
        return 1;
    }

    // ===== mt19937 =====
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(-100, 100);

    vector<int> arr(n);

    // 1. Заполнение
    for (int &x : arr) x = dist(gen);

    cout << "\nИсходный массив:\n";
    for (const int &x : arr) cout << x << " ";
    cout << endl;

    // 2.
    int positiveCount = count_if(arr.begin(), arr.end(),
                                 [](int x) { return x > 0; });

    auto maxIt = max_element(arr.begin(), arr.end(),
                             [](int a, int b) {
                                 return abs(a) < abs(b);
                             });

    int sumAfterMax = 0;
    for (auto it = next(maxIt); it != arr.end(); ++it)
        sumAfterMax += *it;

    cout << "\nКоличество положительных: " << positiveCount << endl;
    cout << "Сумма после максимального по модулю: " << sumAfterMax << endl;

    // 3.
    vector<int> bestSeq, currSeq;

    if (!arr.empty()) {
        currSeq.push_back(arr[0]);

        for (auto it = next(arr.begin()); it != arr.end(); ++it) {
            if (*it > currSeq.back()) {
                currSeq.push_back(*it);
            } else {
                if (currSeq.size() > bestSeq.size())
                    bestSeq = currSeq;
                currSeq = {*it};
            }
        }
        if (currSeq.size() > bestSeq.size())
            bestSeq = currSeq;
    }

    cout << "\nСамая длинная возрастающая последовательность:\n";
    for (const int &x : bestSeq) cout << x << " ";
    cout << endl;

    // 4.
    int pos = count_if(arr.begin(), arr.end(), [](int x) { return x > 0; });
    int neg = count_if(arr.begin(), arr.end(), [](int x) { return x < 0; });

    if (pos > neg) {
        for (int &x : arr) if (x < 0) x = 0;
    } else if (neg > pos) {
        for (int &x : arr) if (x > 0) x = 1;
    }

    cout << "\nМассив после замены:\n";
    for (const int &x : arr) cout << x << " ";
    cout << endl;

    // ===== 5. ТОЧНО КАК В ТАБЛИЦЕ =====
    int cols = 6;
    vector<vector<int>> matrix(n, vector<int>(cols));

    for (int i = 0; i < n; i++) {

        int pairIndex = i / 2;

        int start;
        if (i % 2 == 0) {
            // чётная строка
            start = 50 + pairIndex * 30;

            for (int j = 0; j < cols; j++) {
                matrix[i][j] = start + j * 10;
            }
        } else {
            // нечётная строка
            start = (50 + pairIndex * 30) + 45;

            for (int j = 0; j < cols; j++) {
                matrix[i][j] = start - j * 5;
            }
        }
    }

    cout << "\nМассив N x 6:\n";
    for (const auto &row : matrix) {
        for (const int &x : row) cout << x << "\t";
        cout << endl;
    }

    return 0;
}