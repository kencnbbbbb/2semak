#include "func.h"

#include <cstdlib>
#include <iostream>
#include <limits>

using namespace std;

int positiveMod(int value, int mod) {
    int r = value % mod;
    if (r < 0) r += mod;
    return r;
}

bool isPrime(int n) {
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (int d = 3; d * d <= n; d += 2) {
        if (n % d == 0) return false;
    }
    return true;
}

int gcdSimple(int a, int b) {
    a = abs(a);
    b = abs(b);
    while (b != 0) {
        int r = a % b;
        a = b;
        b = r;
    }
    return a;
}

int multiplyMod(int a, int b, int mod) {
    return positiveMod(positiveMod(a, mod) * positiveMod(b, mod), mod);
}

int powerSimple(int a, int x, int p) {
    int result = 1 % p;
    int base = positiveMod(a, p);
    for (int i = 0; i < x; ++i) {
        result = multiplyMod(result, base, p);
    }
    return result;
}

int powerMod(int a, int x, int p) {
    int result = 1 % p;
    int base = positiveMod(a, p);

    while (x > 0) {
        if (x % 2 == 1) {
            result = multiplyMod(result, base, p);
        }
        base = multiplyMod(base, base, p);
        x /= 2;
    }

    return result;
}

EuclidResult extendedEuclid(int a, int b) {
    int x1 = abs(a), x2 = 1, x3 = 0;
    int y1 = abs(b), y2 = 0, y3 = 1;

    while (y1 != 0) {
        int q = x1 / y1;
        int t1 = x1 - q * y1;
        int t2 = x2 - q * y2;
        int t3 = x3 - q * y3;

        x1 = y1;
        x2 = y2;
        x3 = y3;

        y1 = t1;
        y2 = t2;
        y3 = t3;
    }

    if (a < 0) x2 = -x2;
    if (b < 0) x3 = -x3;

    EuclidResult result;
    result.d = x1;
    result.u = x2;
    result.v = x3;
    return result;
}

string encryptText(const string& text, int key) {
    string result = text;
    int shift = key % 256;

    for (int i = 0; i < (int)result.size(); ++i) {
        result[i] = char((unsigned char)result[i] + shift);
    }

    return result;
}

string decryptText(const string& text, int key) {
    string result = text;
    int shift = key % 256;

    for (int i = 0; i < (int)result.size(); ++i) {
        result[i] = char((unsigned char)result[i] - shift);
    }

    return result;
}

void waitEnter() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\nНажмите Enter для возврата в меню...";
    cin.get();
}
