#include "SocialNetwork.h"
#include <iostream>

using namespace std;

void SocialNetwork::addFriends(const string& a, const string& b) {
    if (friendsMap[a].count(b)) {
        cout << a << " и " << b << " уже друзья" << endl;
    } else {
        friendsMap[a].insert(b);
        friendsMap[b].insert(a);
        cout << a << " и " << b << " теперь друзья" << endl;
    }
}

int SocialNetwork::countFriends(const string& a) {
    return friendsMap[a].size();
}

bool SocialNetwork::areFriends(const string& a, const string& b) {
    // человек считается другом самому себе
    if (a == b) return true;
    return friendsMap[a].count(b) > 0;
}