#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <climits>
#include <algorithm>

using namespace std;

int N, M, variantNumber;

int getIndex(int i, int j) {
    return i * M + j;
}

int boardToMask(const vector<vector<int>>& board) {
    int mask = 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (board[i][j] == 1) {
                int pos = getIndex(i, j);
                mask |= (1 << pos);
            }
        }
    }

    return mask;
}

int makeTargetMask(int firstValue) {
    int mask = 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            int value = 0;

            if (variantNumber == 1) {
                // Шахматный порядок
                if ((i + j) % 2 == 0) {
                    value = firstValue;
                } else {
                    value = 1 - firstValue;
                }
            }
            else if (variantNumber == 2) {
                // Рамка
                bool border = (i == 0 || i == N - 1 || j == 0 || j == M - 1);

                if (border) {
                    value = firstValue;
                } else {
                    value = 1 - firstValue;
                }
            }
            else if (variantNumber == 3) {
                // Верхняя и нижняя половины
                bool upperHalf = (i < N / 2);

                if (upperHalf) {
                    value = firstValue;
                } else {
                    value = 1 - firstValue;
                }
            }

            if (value == 1) {
                int pos = getIndex(i, j);
                mask |= (1 << pos);
            }
        }
    }

    return mask;
}

vector<int> makeMoves() {
    vector<int> moves;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            int current = getIndex(i, j);

            // Сосед справа
            if (j + 1 < M) {
                int right = getIndex(i, j + 1);
                int moveMask = (1 << current) | (1 << right);
                moves.push_back(moveMask);
            }

            // Сосед снизу
            if (i + 1 < N) {
                int down = getIndex(i + 1, j);
                int moveMask = (1 << current) | (1 << down);
                moves.push_back(moveMask);
            }
        }
    }

    return moves;
}

int bfs(int startMask, int targetMask, const vector<int>& moves) {
    if (startMask == targetMask) {
        return 0;
    }

    queue<int> q;
    unordered_map<int, int> distance;

    q.push(startMask);
    distance[startMask] = 0;

    while (!q.empty()) {
        int currentMask = q.front();
        q.pop();

        int currentDistance = distance[currentMask];

        for (int moveMask : moves) {
            int nextMask = currentMask ^ moveMask;

            if (distance.find(nextMask) == distance.end()) {
                distance[nextMask] = currentDistance + 1;

                if (nextMask == targetMask) {
                    return currentDistance + 1;
                }

                q.push(nextMask);
            }
        }
    }

    return -1;
}

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "Введите N и M: ";
    cin >> N >> M;

    if (N * M > 25) {
        cout << "Ошибка: для данного способа решения размер доски должен быть не больше 25 клеток." << endl;
        return 0;
    }

    cout << "Введите номер варианта (1, 2 или 3): ";
    cin >> variantNumber;

    if (variantNumber < 1 || variantNumber > 3) {
        cout << "Ошибка: номер варианта должен быть 1, 2 или 3." << endl;
        return 0;
    }

    vector<vector<int>> board(N, vector<int>(M));

    cout << "Введите доску из 0 и 1:" << endl;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> board[i][j];

            if (board[i][j] != 0 && board[i][j] != 1) {
                cout << "Ошибка: элементы доски должны быть только 0 или 1." << endl;
                return 0;
            }
        }
    }

    int startMask = boardToMask(board);

    vector<int> moves = makeMoves();

    int target1 = makeTargetMask(0);
    int target2 = makeTargetMask(1);

    int result1 = bfs(startMask, target1, moves);
    int result2 = bfs(startMask, target2, moves);

    int answer;

    if (result1 == -1 && result2 == -1) {
        answer = -1;
    }
    else if (result1 == -1) {
        answer = result2;
    }
    else if (result2 == -1) {
        answer = result1;
    }
    else {
        answer = min(result1, result2);
    }

    if (answer == -1) {
        cout << "Невозможно получить нужный рисунок." << endl;
    } else {
        cout << "Минимальное количество ходов: " << answer << endl;
    }

    return 0;
}