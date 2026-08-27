#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <string>
#include <vector>

std::vector<uint8_t> TextToBytes(const std::string& text);
std::string BytesToText(const std::vector<uint8_t>& data);
std::string BytesToHex(const std::vector<uint8_t>& data);
std::vector<uint8_t> HexToBytes(const std::string& hex);
void GenerateRandomBytes(uint8_t* arr, int size);
void SaveKeyToFile(const uint8_t* key, const std::string& filename);
void PrintBlock(const char* title, const uint8_t* block, int size);

#endif
