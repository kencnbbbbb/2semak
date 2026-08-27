#include "tram.h"
#include <algorithm>

Tram::Tram(int name, const std::vector<std::string>& stops) {
    this->name = name;
    this->stops = stops;
}

int Tram::getName() const {
    return name;
}

const std::vector<std::string>& Tram::getStops() const {
    return stops;
}

bool Tram::hasStop(const std::string& stop) const {
    return std::find(stops.begin(), stops.end(), stop) != stops.end();
}
