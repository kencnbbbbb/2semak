#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Candidate {
    string name;
    int score; // Для подсчета баллов в методе Борда
};

// Метод Борда
void bordaMethod(int n, int k, vector<vector<int>>& rankings) {
    vector<Candidate> candidates(n);

    
    // Инициализация кандидатов
    for (int i = 0; i < n; ++i) {
        candidates[i].name = "Кандидат " + to_string(i + 1);
        candidates[i].score = 0;
    }

    // Подсчёт баллов
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < n; ++j) {
            candidates[rankings[i][j] - 1].score += (n - 1 - j); // n-1-j баллов за позицию j
        }
    }

    // Вывод победителя
    sort(candidates.begin(), candidates.end(), [](Candidate& a, Candidate& b) {
        return a.score > b.score;
    });

    cout << "Победитель по методу Борда: " << candidates[0].name << endl;
}

// Метод Кондерсе
void condorcetMethod(int n, int k, vector<vector<int>>& rankings) {
    vector<vector<int>> wins(n, vector<int>(n, 0)); // wins[i][j] = количество побед i над j
    vector<Candidate> candidates(n);

    // Инициализация кандидатов
    for (int i = 0; i < n; ++i) {
        candidates[i].name = "Кандидат " + to_string(i + 1);
    }

    // Сравнение кандидатов
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int l = j + 1; l < n; ++l) {
                if (rankings[i][j] < rankings[i][l]) {
                    wins[j][l]++;
                } else {
                    wins[l][j]++;
                }
            }
        }
    }

    // Находим кандидата, который побеждает во всех сравнениях
    int winner = -1;
    for (int i = 0; i < n; ++i) {
        bool isWinner = true;
        for (int j = 0; j < n; ++j) {
            if (i != j && wins[i][j] <= k / 2) {
                isWinner = false;
                break;
            }
        }
        if (isWinner) {
            winner = i;
            break;
        }
    }

    if (winner != -1) {
        cout << "Победитель по методу Кондерсе: " << candidates[winner].name << endl;
    } else {
        cout << "Нет победителя по методу Кондерсе" << endl;
    }
}

int main() {
    int n, k;

    // Ввод данных
    cout << "Введите количество кандидатов (n): ";
    cin >> n;
    cout << "Введите количество голосующих (k): ";
    cin >> k;

    vector<vector<int>> rankings(k, vector<int>(n));

    cout << "Введите рейтинги от каждого голосующего (1 = первое место, n = последнее место): " << endl;
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> rankings[i][j];
        }
    }

    // Применение методов голосования
    bordaMethod(n, k, rankings);
    condorcetMethod(n, k, rankings);

    return 0;
}
