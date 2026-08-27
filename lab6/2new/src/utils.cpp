#include "utils.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <random>
#include <stdexcept>

std::vector<uint8_t> TextToBytes(const std::string& text) {
    return std::vector<uint8_t>(text.begin(), text.end());
}

std::string BytesToText(const std::vector<uint8_t>& data) {
    return std::string(data.begin(), data.end());
}

std::string BytesToHex(const std::vector<uint8_t>& data) {
    std::stringstream ss;
    for (uint8_t byte : data) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)byte;
    }
    return ss.str();
}

std::vector<uint8_t> HexToBytes(const std::string& hex) {
    if (hex.size() % 2 != 0) {
        throw std::runtime_error("HEX-строка должна иметь четную длину");
    }

    std::vector<uint8_t> bytes;
    for (size_t i = 0; i < hex.size(); i += 2) {
        std::string byteString = hex.substr(i, 2);
        uint8_t byte = (uint8_t)strtol(byteString.c_str(), nullptr, 16);
        bytes.push_back(byte);
    }

    return bytes;
}

void GenerateRandomBytes(uint8_t* arr, int size) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 255);

    for (int i = 0; i < size; i++) {
        arr[i] = (uint8_t)dist(gen);
    }
}

void SaveKeyToFile(const uint8_t* key, const std::string& filename) {
    std::ofstream file(filename);

    for (int i = 0; i < 16; i++) {
        file << std::hex << std::setw(2) << std::setfill('0') << (int)key[i];
    }

    file.close();
}

void PrintBlock(const char* title, const uint8_t* block, int size) {
    std::cout << title;
    for (int i = 0; i < size; i++) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)block[i];
    }
    std::cout << std::dec << std::endl;
}
