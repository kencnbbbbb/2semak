#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <iomanip>

using namespace std;

//ЗАДАНИЕ 1 
void task1() {
    int M = 8, N = 6;
    srand(time(0));

    vector<vector<double>> matrix(M, vector<double>(N));

    // Заполнение
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            matrix[i][j] = -10.0 + (rand() / (double)RAND_MAX) * 20.0;

    cout << "\nМатрица:\n\n";

    // ВЫРОВНЕННЫЙ ВЫВОД
    for (auto &row : matrix) {
        for (auto val : row) {
            cout << setw(10) << fixed << setprecision(3) << val << " ";
        }
        cout << endl;
    }

    // Произведения столбцов
    vector<double> products(N, 1);

    for (int j = 0; j < N; j++)
        for (int i = 0; i < M; i++)
            products[j] *= matrix[i][j];

    cout << "\nВыбор:\n\n";

    for (double p : products) {
        cout << setw(15) << scientific << setprecision(3) << p << " ";
    }
    cout << endl;

    // Поиск min/max
    int minIndex = 0, maxIndex = 0;
    for (int i = 1; i < N; i++) {
        if (products[i] < products[minIndex]) minIndex = i;
        if (products[i] > products[maxIndex]) maxIndex = i;
    }

    cout << "\nМинимальная: " << minIndex << endl;
    cout << "Максимальная: " << maxIndex << endl;
}

//  ЗАДАНИЕ 2 
void task2() {
    int N;
    cout << "\nВведите количество строк: ";
    cin >> N;

    int value = 10;

    cout << endl;
    for (int i = 1; i <= N; i++) {
        for (int j = 0; j < i; j++) {
            cout << setw(5) << value;
            value += 2;
        }
        cout << endl;
    }
}

//  ЗАДАНИЕ 3 
const int ROWS = 20;
const int COLS = 40;

int countNeighbors(vector<vector<int>>& grid, int x, int y) {
    int count = 0;

    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;

            int nx = (x + i + ROWS) % ROWS;
            int ny = (y + j + COLS) % COLS;

            count += grid[nx][ny];
        }

    return count;
}

void task3() {
    srand(time(0));

    vector<vector<int>> grid(ROWS, vector<int>(COLS));

    // случайная генерация
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            grid[i][j] = rand() % 2;

    while (true) {
        system("cls"); // для Windows (Linux → "clear")

        for (auto &row : grid) {
            for (auto cell : row)
                cout << (cell ? "O" : " ");
            cout << endl;
        }

        vector<vector<int>> newGrid = grid;

        for (int i = 0; i < ROWS; i++)
            for (int j = 0; j < COLS; j++) {
                int neighbors = countNeighbors(grid, i, j);

                if (grid[i][j] == 1) {
                    if (neighbors < 2 || neighbors > 3)
                        newGrid[i][j] = 0;
                } else {
                    if (neighbors == 3)
                        newGrid[i][j] = 1;
                }
            }

        grid = newGrid;
        this_thread::sleep_for(chrono::milliseconds(200));
    }
}

// МЕНЮ 
int main() {
    setlocale(LC_ALL, "ru");

    int choice;

    while (true) {
        cout << "\nМЕНЮ\n";
        cout << "1 - Матрица + произведения\n";
        cout << "2 - Треугольная матрица\n";
        cout << "3 - Игра жизни\n";
        cout << "0 - Выход\n";
        cout << "Выбор: ";
        cin >> choice;

        switch (choice) {
            case 1: task1(); break;
            case 2: task2(); break;
            case 3: task3(); break;
            case 0: return 0;
            default: cout << "Неверный выбор\n";
        }
    }
}