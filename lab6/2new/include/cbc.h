#ifndef CBC_H
#define CBC_H

#include <stdint.h>
#include <vector>

std::vector<uint8_t> CBC_Encrypt(const std::vector<uint8_t>& text, const uint8_t* key, const uint8_t* iv, bool showState);
std::vector<uint8_t> CBC_Decrypt(const std::vector<uint8_t>& cipher, const uint8_t* key, const uint8_t* iv, bool showState);

#endif
