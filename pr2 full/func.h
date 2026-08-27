#ifndef FUNC_H
#define FUNC_H

#include <string>

struct EuclidResult {
    int d;
    int u;
    int v;
};

int positiveMod(int value, int mod);
bool isPrime(int n);
int gcdSimple(int a, int b);
int multiplyMod(int a, int b, int mod);
int powerSimple(int a, int x, int p);
int powerMod(int a, int x, int p);
EuclidResult extendedEuclid(int a, int b);
std::string encryptText(const std::string& text, int key);
std::string decryptText(const std::string& text, int key);
void waitEnter();

void runTask1();
void runTask2();
void runTask3();
void runTask4();
void runTask5();
void runTask6();

#endif
