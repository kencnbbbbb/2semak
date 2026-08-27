#ifndef AES_H
#define AES_H

#include <stdint.h>

void AES128_SetShowState(bool value);
void AES128_KeyExpansion(const uint8_t* key, uint8_t* roundKeys);
void AES128_EncryptBlock(const uint8_t* input, const uint8_t* roundKeys, uint8_t* output);
void AES128_DecryptBlock(const uint8_t* input, const uint8_t* roundKeys, uint8_t* output);
void AES128_PrintRoundKeys(const uint8_t* roundKeys);

#endif
