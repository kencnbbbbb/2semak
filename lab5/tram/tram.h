#ifndef TRAM_H
#define TRAM_H

#include <string>
#include <vector>

class Tram {
private:
    int name;
    std::vector<std::string> stops;

public:
    Tram(int name, const std::vector<std::string>& stops);

    int getName() const;
    const std::vector<std::string>& getStops() const;
    bool hasStop(const std::string& stop) const;
};

#endif
