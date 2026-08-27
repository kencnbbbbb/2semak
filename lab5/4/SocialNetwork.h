#ifndef SOCIALNETWORK_H
#define SOCIALNETWORK_H

#include <string>
#include <unordered_map>
#include <unordered_set>

class SocialNetwork {
private:
    std::unordered_map<std::string, std::unordered_set<std::string>> friendsMap;

public:
    void addFriends(const std::string& a, const std::string& b);
    int countFriends(const std::string& a);
    bool areFriends(const std::string& a, const std::string& b);
};

#endif