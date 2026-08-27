#include "tram_system.h"
#include <iostream>
#include <sstream>
#include <set>

using namespace std;

CommandType TramSystem::getCommandType(const string& command) const {
    if (command == "CREATE_TRAM") return CommandType::CREATE_TRAM;
    if (command == "TRAMS_IN_STOP") return CommandType::TRAMS_IN_STOP;
    if (command == "STOPS_IN_TRAM") return CommandType::STOPS_IN_TRAM;
    if (command == "TRAMS") return CommandType::TRAMS;
    return CommandType::UNKNOWN;
}

bool TramSystem::tramExists(int name) const {
    for (const Tram& tram : trams) {
        if (tram.getName() == name) return true;
    }
    return false;
}

bool TramSystem::stopExists(const string& stop) const {
    for (const Tram& tram : trams) {
        if (tram.hasStop(stop)) return true;
    }
    return false;
}

bool TramSystem::hasDuplicateStops(const vector<string>& stops) const {
    set<string> uniqueStops;
    for (const string& stop : stops) {
        if (uniqueStops.count(stop) > 0) return true;
        uniqueStops.insert(stop);
    }
    return false;
}

bool TramSystem::hasSameStops(const vector<string>& stops) const {
    set<string> newStops(stops.begin(), stops.end());

    for (const Tram& tram : trams) {
        const vector<string>& oldStopsVector = tram.getStops();
        set<string> oldStops(oldStopsVector.begin(), oldStopsVector.end());

        if (oldStops == newStops) return true;
    }
    return false;
}

vector<int> TramSystem::getTramsByStop(const string& stop, int exceptTram) const {
    vector<int> result;

    for (const Tram& tram : trams) {
        if (tram.getName() != exceptTram && tram.hasStop(stop)) {
            result.push_back(tram.getName());
        }
    }

    return result;
}

void TramSystem::createTram(int name, const vector<string>& stops) {
    if (tramExists(name)) {
        cout << "Ошибка: Трамвай с именем " << name << " уже создан" << endl;
        return;
    }

    if (stops.size() < 2) {
        cout << "Ошибка: Трамвай не может быть создан с одной остановкой" << endl;
        return;
    }

    if (hasDuplicateStops(stops)) {
        cout << "Ошибка: Трамвай не может быть создан с двумя одинаковыми остановками" << endl;
        return;
    }

    if (hasSameStops(stops)) {
        cout << "Ошибка: Трамвай с таким набором остановок уже существует" << endl;
        return;
    }

    trams.push_back(Tram(name, stops));
    cout << "Трамвай " << name << " создан" << endl;
}

void TramSystem::printTramsInStop(const string& stop) const {
    if (!stopExists(stop)) {
        cout << "Ошибка: Остановка " << stop << " не найдена" << endl;
        return;
    }

    vector<int> result = getTramsByStop(stop);

    cout << "Трамваи на остановке " << stop << ":";
    for (int name : result) {
        cout << " " << name;
    }
    cout << endl;
}

void TramSystem::printStopsInTram(int name) const {
    for (const Tram& tram : trams) {
        if (tram.getName() == name) {
            cout << "Остановки трамвая " << name << ":" << endl;

            for (const string& stop : tram.getStops()) {
                cout << "  " << stop << ":";

                vector<int> otherTrams = getTramsByStop(stop, name);
                if (otherTrams.empty()) {
                    cout << " нет других трамваев";
                } else {
                    cout << " трамваи";
                    for (int otherName : otherTrams) {
                        cout << " " << otherName;
                    }
                }
                cout << endl;
            }
            return;
        }
    }

    cout << "Ошибка: Трамвай " << name << " не найден" << endl;
}

void TramSystem::printAllTrams() const {
    if (trams.empty()) {
        cout << "Ошибка: Трамваи не найдены" << endl;
        return;
    }

    cout << "Список трамваев:" << endl;
    for (const Tram& tram : trams) {
        cout << "Трамвай " << tram.getName() << ":";
        for (const string& stop : tram.getStops()) {
            cout << " " << stop;
        }
        cout << endl;
    }
}

void TramSystem::run() {
    string line;

    while (true) {
        cout << ">>> ";

        if (!getline(cin, line)) break;
        if (line == "EXIT") break;
        if (line.empty()) continue;

        stringstream input(line);
        string command;
        input >> command;

        CommandType type = getCommandType(command);

        switch (type) {
            case CommandType::CREATE_TRAM: {
                int name, countStops;
                input >> name >> countStops;

                if (!input || countStops <= 0) {
                    cout << "Ошибка: Неверный формат команды CREATE_TRAM" << endl;
                    break;
                }

                vector<string> stops;
                string stop;
                while (input >> stop) {
                    stops.push_back(stop);
                }

                if ((int)stops.size() != countStops) {
                    cout << "Ошибка: Количество остановок не совпадает с N" << endl;
                    break;
                }

                createTram(name, stops);
                break;
            }

            case CommandType::TRAMS_IN_STOP: {
                string stop;
                input >> stop;

                if (stop.empty()) {
                    cout << "Ошибка: Не указана остановка" << endl;
                    break;
                }

                printTramsInStop(stop);
                break;
            }

            case CommandType::STOPS_IN_TRAM: {
                int name;
                input >> name;

                if (!input) {
                    cout << "Ошибка: Не указан номер трамвая" << endl;
                    break;
                }

                printStopsInTram(name);
                break;
            }

            case CommandType::TRAMS: {
                printAllTrams();
                break;
            }

            default: {
                cout << "Ошибка: Неизвестная команда" << endl;
                break;
            }
        }
    }
}
