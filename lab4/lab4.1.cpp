#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;
const double EPS = 1e-4;
const int MAX_ITER = 100;
// структура строки таблицы
struct Iteration {
    int n;
    double xn;
    double xn1;
    double diff;
};

// функция
double f(double x) {
    return x * x - 3 * sin(x);
}

// производная
double df(double x) {
    return 2 * x - 3 * cos(x);
}

// для итераций
double g(double x) {
    return sqrt(3 * sin(x));
}

// ---------------- НЬЮТОН ----------------
vector<Iteration> newton(double x0) {
    vector<Iteration> table;

    double x = x0;

    for (int n = 0; n < MAX_ITER; ++n) {
        double x1 = x - f(x) / df(x);
        double diff = fabs(x1 - x);

        table.push_back({n, x, x1, diff});

        if (diff < EPS)
            break;

        x = x1;
    }

    return table;
}

// ---------------- БИСЕКЦИЯ ----------------
vector<Iteration> bisection(double a, double b) {
    vector<Iteration> table;

    double prev = a;

    for (int n = 0; n < MAX_ITER; ++n) {
        double c = (a + b) / 2.0;
        double diff = fabs(b - a);

        table.push_back({n, a, b, diff});

        if (diff < EPS)
            break;

        if (f(a) * f(c) < 0)
            b = c;
        else
            a = c;

        prev = c;
    }

    return table;
}

// ---------------- ПРОСТЫЕ ИТЕРАЦИИ ----------------
vector<Iteration> simple_iteration(double x0) {
    vector<Iteration> table;

    double x = x0;

    for (int n = 0; n < MAX_ITER; ++n) {

        if (sin(x) < 0) break; // защита

        double x1 = g(x);
        double diff = fabs(x1 - x);

        table.push_back({n, x, x1, diff});

        if (diff < EPS)
            break;

        x = x1;
    }

    return table;
}

// ---------------- ВЫВОД ----------------
void printTable(const vector<Iteration>& table) {
    cout << "N\txn\t\txn+1\t\tdelta\n";

    for (const auto& row : table) {   // range-based for
        cout << row.n << "\t"
             << row.xn << "\t"
             << row.xn1 << "\t"
             << row.diff << endl;
    }

    if (!table.empty())
        cout << "Корень ≈ " << table.back().xn1 << endl;
}

// ---------------- MAIN ----------------
int main() {
    cout << fixed << setprecision(6);

    cout << "\n=== Корень на [1,2] ===\n";

    cout << "\nМетод бисекции:\n";
    auto bis = bisection(1, 2);
    printTable(bis);

    cout << "\nМетод Ньютона:\n";
    auto newt = newton(1.5);
    printTable(newt);

    cout << "\nМетод простых итераций:\n";
    auto iter = simple_iteration(1.5);
    printTable(iter);

    return 0;
}