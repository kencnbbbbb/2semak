#ifndef CBC_H
#define CBC_H

#include "aes.h"
#include <string>
#include <vector>

std::vector<Byte> encryptCBC(const std::string& text, const Block& key, const Block& iv, bool verbose);
std::string decryptCBC(const std::vector<Byte>& cipher, const Block& key, const Block& iv, bool verbose);

std::vector<Byte> pkcs7Pad(const std::vector<Byte>& data);
std::vector<Byte> pkcs7Unpad(const std::vector<Byte>& data);

#endif
