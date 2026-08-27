#ifndef COMMAND_TYPE_H
#define COMMAND_TYPE_H

// Все команды храним в enum, как требуется в задании.
enum class CommandType {
    CREATE_TRAM,
    TRAMS_IN_STOP,
    STOPS_IN_TRAM,
    TRAMS,
    UNKNOWN
};

#endif
