#ifndef TRAM_H
#define TRAM_H

#include <string>
#include <vector>
#include <map>
#include <set>

// 🔹 enum для команд (по заданию)
enum class Type {
    CREATE_TRAM,
    TRAMS_IN_STOP,
    STOPS_IN_TRAM,
    TRAMS,
    UNKNOWN
};

// 🔹 парсинг команды
Type parseCommand(const std::string& cmd);

class TramSystem {
private:
    std::map<std::string, std::vector<std::string>> tramToStops;
    std::map<std::string, std::set<std::string>> stopToTrams;

public:
    void createTram(const std::string& tramName, const std::vector<std::string>& stops);
    void tramsInStop(const std::string& stop) const;
    void stopsInTram(const std::string& tram) const;
    void printTrams() const;
};

#endif