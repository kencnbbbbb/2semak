#include <iostream>
#include <string>
#include <vector>
#include "tram.h"

int main() {
    TramSystem system;
    std::string command;

    while (std::cin >> command) {
        Type type = parseCommand(command);

        switch (type) {

            case Type::CREATE_TRAM: {
                std::string tramName, stop;
                std::cin >> tramName;

                std::vector<std::string> stops;

                while (std::cin.peek() != '\n' && std::cin >> stop) {
                    stops.push_back(stop);
                }

                system.createTram(tramName, stops);
                break;
            }

            case Type::TRAMS_IN_STOP: {
                std::string stop;
                std::cin >> stop;
                system.tramsInStop(stop);
                break;
            }

            case Type::STOPS_IN_TRAM: {
                std::string tram;
                std::cin >> tram;
                system.stopsInTram(tram);
                break;
            }

            case Type::TRAMS: {
                system.printTrams();
                break;
            }

            default:
                std::cout << "Unknown command" << std::endl;
        }
    }

    return 0;
}