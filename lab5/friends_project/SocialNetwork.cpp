#include "SocialNetwork.h"
#include <iostream>

void SocialNetwork::addFriends(const std::string& firstName, const std::string& secondName) {
    if (firstName == secondName) {
        friendsList[firstName];
        return;
    }

    if (areFriends(firstName, secondName)) {
        std::cout << firstName << " и " << secondName << " уже друзья" << std::endl;
        return;
    }

    friendsList[firstName].insert(secondName);
    friendsList[secondName].insert(firstName);

    std::cout << firstName << " и " << secondName << " теперь друзья" << std::endl;
}

int SocialNetwork::countFriends(const std::string& name) const {
    auto person = friendsList.find(name);

    if (person == friendsList.end()) {
        return 0;
    }

    return static_cast<int>(person->second.size());
}

bool SocialNetwork::areFriends(const std::string& firstName, const std::string& secondName) const {
    if (firstName == secondName) {
        return true;
    }

    auto person = friendsList.find(firstName);

    if (person == friendsList.end()) {
        return false;
    }

    return person->second.count(secondName) > 0;
}
