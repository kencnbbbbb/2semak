#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>

using namespace std;

const int N = 4;
const double EPS = 1e-3;

void printExtended(double a[N][N + 1]) {
    cout << fixed << setprecision(6);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= N; j++) {
            cout << setw(12) << a[i][j];
        }
        cout << endl;
    }

    cout << endl;
}
void gauss(double A[N][N], double B[N], double x[N]) {
    double a[N][N + 1];

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            a[i][j] = A[i][j];
        }
        a[i][N] = B[i];
    }

    cout << "\nМетод Гаусса с выбором главного элемента\n\n";
    cout << "Исходная расширенная матрица:\n";
    printExtended(a);

    // Прямой ход
    for (int k = 0; k < N; k++) {
        int mainRow = k;

        for (int i = k + 1; i < N; i++) {
            if (fabs(a[i][k]) > fabs(a[mainRow][k])) {
                mainRow = i;
            }
        }

        if (mainRow != k) {
            for (int j = 0; j <= N; j++) {
                swap(a[k][j], a[mainRow][j]);
            }
        }

        for (int i = k + 1; i < N; i++) {
            double m = a[i][k] / a[k][k];

            for (int j = k; j <= N; j++) {
                a[i][j] -= m * a[k][j];
            }
        }

        cout << "Матрица после шага " << k + 1 << ":\n";
        printExtended(a);
    }
    // Обратный ход
    for (int i = N - 1; i >= 0; i--) {
        double sum = a[i][N];

        for (int j = i + 1; j < N; j++) {
            sum -= a[i][j] * x[j];
        }

        x[i] = sum / a[i][i];
    }

    cout << "Решение методом Гаусса:\n";
    for (int i = 0; i < N; i++) {
        cout << "x" << i + 1 << " = " << x[i] << endl;
    }
}

void seidel(double A[N][N], double B[N], double x[N]) {
    for (int i = 0; i < N; i++) {
        x[i] = 0;
    }
    cout << "\nМетод Зейделя\n\n";
    cout << "Канонический вид:\n";
    cout << "x1 = (-1.24 + 0.04*x2 - 0.21*x3 + 1.16*x4) / 0.79\n";
    cout << "x2 = (-0.86 - 0.25*x1 - 0.18*x3 + 0.09*x4) / (-1.23)\n";
    cout << "x3 = (2.56 + 0.21*x1 - 0.18*x2 + 0.13*x4) / 0.8\n";
    cout << "x4 = (0.79 - 0.15*x1 + 1.31*x2 - 0.06*x3) / (-0.86)\n\n";

    cout << setw(5) << "N"
         << setw(12) << "x1"
         << setw(12) << "x2"
         << setw(12) << "x3"
         << setw(12) << "x4"
         << setw(12) << "eps" << endl;

    int iter = 0;
    double error;

    do {
        iter++;

        double old[N];

        for (int i = 0; i < N; i++) {
            old[i] = x[i];
        }

        for (int i = 0; i < N; i++) {
            double sum = B[i];

            for (int j = 0; j < N; j++) {
                if (i != j) {
                    sum -= A[i][j] * x[j];
                }
            }

            x[i] = sum / A[i][i];
        }

        error = fabs(x[0] - old[0]);

        for (int i = 1; i < N; i++) {
            error = max(error, fabs(x[i] - old[i]));
        }
        cout << setw(5) << iter
             << setw(12) << fixed << setprecision(6) << x[0]
             << setw(12) << x[1]
             << setw(12) << x[2]
             << setw(12) << x[3]
             << setw(12) << error << endl;

    } while (error > EPS);
    cout << "\nРешение методом Зейделя:\n";
    for (int i = 0; i < N; i++) {
        cout << "x" << i + 1 << " = " << x[i] << endl;
    }
}
int main() {
    setlocale(LC_ALL, "Russian");
    double M = 0.79;
    double K = 0.18;
    double P = -0.86;
    double A[N][N] = {
        { M,    -0.04,  0.21, -1.16 },
        { 0.25, -1.23,  K,    -0.09 },
        { -0.21, K,     0.8,  -0.13 },
        { 0.15, -1.31,  0.06,  P    }
    };
    double B[N] = {
        -1.24,
        P,
        2.56,
        M
    };
    double xGauss[N];
    double xSeidel[N];
    cout << "Вариант 6\n";
    cout << "M = " << M << ", N = " << K << ", P = " << P << endl;
    gauss(A, B, xGauss);
    seidel(A, B, xSeidel);
    cout << "\nИтоговый ответ:\n";
    cout << fixed << setprecision(6);
    for (int i = 0; i < N; i++) {
        cout << "x" << i + 1 << " = " << xGauss[i] << endl;
    }
    return 0;
}