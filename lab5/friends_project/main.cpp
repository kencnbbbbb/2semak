#include <iostream>
#include <string>
#include "SocialNetwork.h"
using namespace std;

int main() {
    SocialNetwork network;

    int n;

    cout << "Введите количество запросов (N):" << endl;
    cout << ">>> ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        string command;

        cout << ">>> ";
        cin >> command;

        if (command == "FRIENDS") {
            string firstName, secondName;
            cin >> firstName >> secondName;

            network.addFriends(firstName, secondName);
        }
        else if (command == "COUNT") {
            string name;
            cin >> name;

            cout << network.countFriends(name) << endl;
        }
        else if (command == "QUESTION") {
            string firstName, secondName;
            cin >> firstName >> secondName;

            if (network.areFriends(firstName, secondName)) {
                cout << "Yes" << endl;
            }
            else {
                cout << "No" << endl;
            }
        }
        else {
            cout << "Неизвестная команда" << endl;
        }
    }

    return 0;
}
