#include "tram.h"
#include <iostream>

// 🔹 преобразование строки в enum
Type parseCommand(const std::string& cmd) {
    if (cmd == "CREATE_TRAM") return Type::CREATE_TRAM;
    if (cmd == "TRAMS_IN_STOP") return Type::TRAMS_IN_STOP;
    if (cmd == "STOPS_IN_TRAM") return Type::STOPS_IN_TRAM;
    if (cmd == "TRAMS") return Type::TRAMS;
    return Type::UNKNOWN;
}

// 🔹 1. CREATE_TRAM
void TramSystem::createTram(const std::string& tramName, const std::vector<std::string>& stops) {
    tramToStops[tramName] = stops;

    for (const std::string& stop : stops) {
        stopToTrams[stop].insert(tramName);
    }
}

// 🔹 2. TRAMS_IN_STOP
void TramSystem::tramsInStop(const std::string& stop) const {
    auto it = stopToTrams.find(stop);

    if (it == stopToTrams.end()) {
        std::cout << "Trams is absent" << std::endl;
        return;
    }

    for (const std::string& tram : it->second) {
        std::cout << tram << " ";
    }
    std::cout << std::endl;
}

// 🔹 3. STOPS_IN_TRAM (по фото!)
void TramSystem::stopsInTram(const std::string& tram) const {
    auto it = tramToStops.find(tram);

    if (it == tramToStops.end()) {
        std::cout << "Stops is absent" << std::endl;
        return;
    }

    for (const std::string& stop : it->second) {
        std::cout << "Stop " << stop << ": ";

        const auto& trams = stopToTrams.at(stop);

        bool hasOther = false;

        for (const std::string& otherTram : trams) {
            if (otherTram != tram) {
                std::cout << otherTram << " ";
                hasOther = true;
            }
        }

        // 🔴 строго по условию
        if (!hasOther) {
            std::cout << "no interchange";
        }

        std::cout << std::endl;
    }
}

// 🔹 4. TRAMS
void TramSystem::printTrams() const {
    if (tramToStops.empty()) {
        std::cout << "Trams is absent" << std::endl;
        return;
    }

    for (const auto& [tram, stops] : tramToStops) {
        std::cout << tram << ": ";
        for (const std::string& stop : stops) {
            std::cout << stop << " ";
        }
        std::cout << std::endl;
    }
}