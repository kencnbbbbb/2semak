Многофайловый проект ENUM C++: график движения трамваев

Файлы проекта:
1) main.cpp          - запуск программы
2) command_type.h   - enum class CommandType со всеми командами
3) tram.h           - описание класса Tram
4) tram.cpp         - реализация класса Tram
5) tram_system.h    - описание класса TramSystem
6) tram_system.cpp  - вся логика команд

Команды:
CREATE_TRAM tram N stop1 stop2 ... stopN
TRAMS_IN_STOP stop
STOPS_IN_TRAM tram
TRAMS
EXIT

Компиляция:
g++ main.cpp tram.cpp tram_system.cpp -o tram_app

Запуск на macOS/Linux:
./tram_app

Запуск на Windows после компиляции MinGW:
tram_app.exe
