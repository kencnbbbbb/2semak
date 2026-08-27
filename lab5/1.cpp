#include <iostream>
#include <string>
#include <map>
#include <iomanip>

using namespace std;

const int ZONES = 3;
const int RACKS = 16;
const int SECTIONS = 8;
const int SHELVES = 6;
const int CELL_CAPACITY = 10;

struct Cell {
    map<string, int> products;
};

Cell warehouse[ZONES][RACKS][SECTIONS][SHELVES];

int getZoneIndex(char zone) {
    if (zone == 'A') return 0;
    if (zone == 'B') return 1;
    if (zone == 'C') return 2;
    return -1;
}

int getCellCount(Cell& cell) {
    int sum = 0;

    for (auto product : cell.products) {
        sum += product.second;
    }

    return sum;
}

bool parseAddress(string address, int& z, int& r, int& s, int& sh) {
    if (address.length() < 4 || address.length() > 5) {
        return false;
    }

    z = getZoneIndex(address[0]);

    if (z == -1) {
        return false;
    }

    string numbers = address.substr(1);

    if (numbers.length() == 3) {
        r = numbers[0] - '0';
        s = numbers[1] - '0';
        sh = numbers[2] - '0';
    }
    else {
        r = stoi(numbers.substr(0, 2));
        s = numbers[2] - '0';
        sh = numbers[3] - '0';
    }

    if (r < 1 || r > RACKS) return false;
    if (s < 1 || s > SECTIONS) return false;
    if (sh < 1 || sh > SHELVES) return false;

    r--;
    s--;
    sh--;

    return true;
}

string makeAddress(int z, int r, int s, int sh) {
    char zone = 'A' + z;
    return string(1, zone) + to_string(r + 1) + to_string(s + 1) + to_string(sh + 1);
}

void addProduct(string name, int count, string address) {
    int z, r, s, sh;

    if (!parseAddress(address, z, r, s, sh)) {
        cout << "Ошибка: Неверный адрес ячейки" << endl;
        return;
    }

    Cell& cell = warehouse[z][r][s][sh];

    int currentCount = getCellCount(cell);

    if (!cell.products.empty() && cell.products.find(name) == cell.products.end()) {
        cout << "Ошибка: Ячейка " << address << " занята другим товаром" << endl;
        return;
    }

    if (cell.products.find(name) != cell.products.end()) {
        cout << "Ошибка: Ячейка " << address << " занята товаром " << name << endl;
        return;
    }

    if (currentCount + count > CELL_CAPACITY) {
        cout << "Ошибка: Превышена вместимость ячейки (максимум 10)" << endl;
        return;
    }

    cell.products[name] += count;

    cout << "Добавлено " << count << " " << name << " в " << address << endl;
}

void removeProduct(string name, int count, string address) {
    int z, r, s, sh;

    if (!parseAddress(address, z, r, s, sh)) {
        cout << "Ошибка: Неверный адрес ячейки" << endl;
        return;
    }

    Cell& cell = warehouse[z][r][s][sh];

    if (cell.products.find(name) == cell.products.end()) {
        cout << "Ошибка: Товар " << name << " не найден в ячейке " << address << endl;
        return;
    }

    if (cell.products[name] < count) {
        cout << "Ошибка: Недостаточно товаров для удаления" << endl;
        return;
    }

    cell.products[name] -= count;

    cout << "Удалено " << count << " " << name;

    if (cell.products[name] > 0) {
        cout << " (остаток: " << cell.products[name] << ")";
    }

    cout << endl;

    if (cell.products[name] == 0) {
        cell.products.erase(name);
    }
}

void info() {
    int totalCapacity = ZONES * RACKS * SECTIONS * SHELVES * CELL_CAPACITY;
    int totalCount = 0;
    int zoneCount[ZONES] = {0, 0, 0};

    for (int z = 0; z < ZONES; z++) {
        for (int r = 0; r < RACKS; r++) {
            for (int s = 0; s < SECTIONS; s++) {
                for (int sh = 0; sh < SHELVES; sh++) {
                    int count = getCellCount(warehouse[z][r][s][sh]);

                    totalCount += count;
                    zoneCount[z] += count;
                }
            }
        }
    }

    cout << fixed << setprecision(2);

    cout << "Загруженность склада: "
         << (double)totalCount / totalCapacity * 100 << " %" << endl;

    int zoneCapacity = RACKS * SECTIONS * SHELVES * CELL_CAPACITY;

    for (int z = 0; z < ZONES; z++) {
        cout << "Загруженность зоны " << char('A' + z) << ": "
             << (double)zoneCount[z] / zoneCapacity * 100 << " %" << endl;
    }

    cout << "Заполненные ячейки:" << endl;

    bool hasFilledCells = false;

    for (int z = 0; z < ZONES; z++) {
        for (int r = 0; r < RACKS; r++) {
            for (int s = 0; s < SECTIONS; s++) {
                for (int sh = 0; sh < SHELVES; sh++) {
                    Cell& cell = warehouse[z][r][s][sh];

                    if (!cell.products.empty()) {
                        hasFilledCells = true;

                        cout << makeAddress(z, r, s, sh) << ": ";

                        for (auto product : cell.products) {
                            cout << product.first << " (" << product.second << ")";
                        }

                        cout << endl;
                    }
                }
            }
        }
    }

    if (!hasFilledCells) {
        cout << "Нет заполненных ячеек" << endl;
    }

    cout << "Пустые ячейки:" << endl;

    int printed = 0;

    for (int z = 0; z < ZONES; z++) {
        for (int r = 0; r < RACKS; r++) {
            for (int s = 0; s < SECTIONS; s++) {
                for (int sh = 0; sh < SHELVES; sh++) {
                    if (warehouse[z][r][s][sh].products.empty()) {
                        cout << makeAddress(z, r, s, sh);

                        printed++;

                        if (printed == 20) {
                            cout << ", ... (список адресов)";
                            cout << endl;
                            return;
                        }
                        else {
                            cout << ", ";
                        }
                    }
                }
            }
        }
    }

    cout << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");

    string command;

    while (true) {
        cout << ">>> ";
        cin >> command;

        if (command == "ADD") {
            string name;
            int count;
            string address;

            cin >> name >> count >> address;

            addProduct(name, count, address);
        }
        else if (command == "REMOVE") {
            string name;
            int count;
            string address;

            cin >> name >> count >> address;

            removeProduct(name, count, address);
        }
        else if (command == "INFO") {
            info();
        }
        else if (command == "EXIT") {
            break;
        }
        else {
            cout << "Ошибка: Неизвестная команда" << endl;
        }
    }

    return 0;
}