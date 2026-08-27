#include "utils.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <stdexcept>

Block generateRandomBlock() {
    Block block{};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 255);
    for (Byte& b : block) b = (Byte)dist(gen);
    return block;
}

void saveKeyToFile(const Block& key, const std::string& filename) {
    std::ofstream file(filename);
    if (!file) throw std::runtime_error("Не удалось открыть файл для записи ключа");
    file << blockToHex(key);
}

Block readKeyFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) throw std::runtime_error("Не удалось открыть файл с ключом");
    std::string hex;
    file >> hex;
    std::vector<Byte> bytes = hexToBytes(hex);
    if (bytes.size() != 16) throw std::runtime_error("Ключ в файле должен содержать 16 байт");
    Block key{};
    for (int i = 0; i < 16; ++i) key[i] = bytes[i];
    return key;
}

std::string bytesToHex(const std::vector<Byte>& data) {
    std::ostringstream oss;
    for (Byte b : data) oss << std::hex << std::setw(2) << std::setfill('0') << (int)b;
    return oss.str();
}

std::string blockToHex(const Block& block) {
    std::ostringstream oss;
    for (Byte b : block) oss << std::hex << std::setw(2) << std::setfill('0') << (int)b;
    return oss.str();
}

std::vector<Byte> hexToBytes(const std::string& hex) {
    if (hex.size() % 2 != 0) throw std::runtime_error("HEX-строка должна иметь четную длину");
    std::vector<Byte> data;
    for (size_t i = 0; i < hex.size(); i += 2) {
        std::string part = hex.substr(i, 2);
        Byte b = (Byte)std::stoul(part, nullptr, 16);
        data.push_back(b);
    }
    return data;
}

void printBlock(const std::string& title, const Block& block) {
    std::cout << title << ": " << blockToHex(block) << std::endl;
}

void printBytes(const std::string& title, const std::vector<Byte>& data) {
    std::cout << title << ": " << bytesToHex(data) << std::endl;
}
