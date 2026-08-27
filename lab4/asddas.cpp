#include <iostream>
#include <vector>
using namespace std;

// Функция объявляет вектор, считает сумму и произведение элементов, возвращает их через параметры
void calculate(vector<int>& vec, int& sum, int& product) {
    vec = {3, 5, 7}; // объявление и инициализация вектора
    sum = 0;
    product = 1;
    for (int num : vec) {
        sum += num;
        product *= num;
    }
}

int main() {
    vector<int> numbers;
    int sum, product;
    calculate(numbers, sum, product);
    cout << "Сумма: " << sum << endl;
    cout << "Произведение: " << product << endl;
    return 0;