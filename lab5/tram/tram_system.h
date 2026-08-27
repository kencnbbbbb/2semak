#ifndef TRAM_SYSTEM_H
#define TRAM_SYSTEM_H

#include "tram.h"
#include "command_type.h"
#include <string>
#include <vector>

class TramSystem {
private:
    std::vector<Tram> trams;

    bool tramExists(int name) const;
    bool stopExists(const std::string& stop) const;
    bool hasSameStops(const std::vector<std::string>& stops) const;
    bool hasDuplicateStops(const std::vector<std::string>& stops) const;
    std::vector<int> getTramsByStop(const std::string& stop, int exceptTram = -1) const;
    CommandType getCommandType(const std::string& command) const;

public:
    void run();

    void createTram(int name, const std::vector<std::string>& stops);
    void printTramsInStop(const std::string& stop) const;
    void printStopsInTram(int name) const;
    void printAllTrams() const;
};

#endif
