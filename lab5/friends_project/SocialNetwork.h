#ifndef SOCIALNETWORK_H
#define SOCIALNETWORK_H

#include <map>
#include <set>
#include <string>

class SocialNetwork {
private:
    std::map<std::string, std::set<std::string>> friendsList;

public:
    void addFriends(const std::string& firstName, const std::string& secondName);
    int countFriends(const std::string& name) const;
    bool areFriends(const std::string& firstName, const std::string& secondName) const;
};

#endif
