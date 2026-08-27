#ifndef UTILS_H
#define UTILS_H

#include "aes.h"
#include <string>
#include <vector>

Block generateRandomBlock();
void saveKeyToFile(const Block& key, const std::string& filename);
Block readKeyFromFile(const std::string& filename);

std::string bytesToHex(const std::vector<Byte>& data);
std::string blockToHex(const Block& block);
std::vector<Byte> hexToBytes(const std::string& hex);

void printBlock(const std::string& title, const Block& block);
void printBytes(const std::string& title, const std::vector<Byte>& data);

#endif
