#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

const double EPS = 1e-4;
const int MAX_ITER = 100;

double f(double x){
    return sin(x+1) - 0.2 * x;
}

double df(double x) {
    return cos(x + 1) - 0.2;
}

double g(double x) {
    return sin(x + 1) / 0.2;
}

//Метод половинного деления
void bisection(double a, double b){
    cout << "\nМетод половинного деления:\n";
    cout << "N\tan\t\tbn\t\tbn - an\n";
    for (int n = 0;n < MAX_ITER; ++n){
        double c = (a+b) / 2.0;
        cout << n << "\t" << fixed << setprecision(6) << a << "\t" << b << "\t" << b - a << endl;
        if(fabs(b-a) < EPS){
            cout << "Корень ≈ " << c << endl;
            return;
        }
        if (f(a) * f(c) < 0)
            b = c;
        else;
            a = c;
        
    }
    cout << "Достигнуто максимальное число итераций.\n";

}

//Метод Ньютона
void newton(double x){
    cout << "\nМетод Ньютона:\n";
    cout << "N\txn\t\txn+1\t\tdelta\n";
    
    for (int n = 0; n < MAX_ITER; ++n){
        double x1 = x - f(x) / df(x);
        cout << n << "\t" << x << "\t" << x1 << "\t" << fabs(x1 - x) << endl;
        if (fabs(x1-x) < EPS){
            cout << "Корень ≈ " << x1 << endl;
            return;
        }
        x = x1;
    }
    cout << "Достигнуто максимальное число итераций.\n";
}

//Метод простых итераций
void easyiter(double x){
    cout << "\nМетод простых итераций:\n";
    cout << "N\txn\t\txn+1\t\tdelta\n";
    for (int n = 0; n < MAX_ITER; ++n) {
        double x1 = g(x);
        cout << n << "\t" << x << "\t" << x1 << "\t" << fabs(x1 - x) << endl;
               if (fabs(x1 - x) < EPS) {
                   cout << "Корень ≈ " << x1 << endl;
                   return;
               }
               x = x1;
           }
           cout << "Достигнуто максимальное число итераций.\n";
}

int main() {
    // Первый корень
    bisection(-3, -2);
    newton(-2.5);
    easyiter(-2.5);

    // Второй корень
    bisection(0, 1);
    newton(0.5);
    easyiter(0.5);

    // Третий корень
    bisection(2, 3);
    newton(2.5);
    easyiter(2.5);

    return 0;
}
