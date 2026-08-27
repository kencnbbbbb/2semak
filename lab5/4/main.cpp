#include <iostream>
#include "SocialNetwork.h"

using namespace std;

int main() {
    int N;
    cout << "Введите количество запросов (N): ";
    cin >> N;

    SocialNetwork sn;

    while (N--) {
        string command;
        cin >> command;

        if (command == "FRIENDS") {
            string a, b;
            cin >> a >> b;
            sn.addFriends(a, b);

        } else if (command == "COUNT") {
            string a;
            cin >> a;
            cout << sn.countFriends(a) << endl;

        } else if (command == "QUESTION") {
            string a, b;
            cin >> a >> b;
            cout << (sn.areFriends(a, b) ? "Yes" : "No") << endl;
        }
    }

    return 0;
}