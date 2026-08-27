#include "cbc.h"
#include "aes.h"
#include <stdexcept>

static std::vector<uint8_t> AddPadding(std::vector<uint8_t> data) {
    int padding = 16 - (data.size() % 16);
    if (padding == 0) padding = 16;

    for (int i = 0; i < padding; i++) {
        data.push_back((uint8_t)padding);
    }

    return data;
}

static void RemovePadding(std::vector<uint8_t>& data) {
    if (data.empty()) return;

    uint8_t padding = data.back();
    if (padding == 0 || padding > 16 || padding > data.size()) {
        throw std::runtime_error("Ошибка PKCS7 Padding при расшифровании");
    }

    for (int i = 0; i < padding; i++) {
        if (data[data.size() - 1 - i] != padding) {
            throw std::runtime_error("Ошибка PKCS7 Padding при расшифровании");
        }
    }

    data.resize(data.size() - padding);
}

std::vector<uint8_t> CBC_Encrypt(const std::vector<uint8_t>& text, const uint8_t* key, const uint8_t* iv, bool showState) {
    uint8_t roundKeys[176];
    AES128_KeyExpansion(key, roundKeys);
    AES128_SetShowState(showState);

    if (showState) {
        AES128_PrintRoundKeys(roundKeys);
    }

    std::vector<uint8_t> data = AddPadding(text);
    std::vector<uint8_t> result(data.size());

    uint8_t previousBlock[16];
    for (int i = 0; i < 16; i++) previousBlock[i] = iv[i];

    for (size_t block = 0; block < data.size(); block += 16) {
        uint8_t inputBlock[16];
        uint8_t outputBlock[16];

        for (int i = 0; i < 16; i++) {
            inputBlock[i] = data[block + i] ^ previousBlock[i];
        }

        AES128_EncryptBlock(inputBlock, roundKeys, outputBlock);

        for (int i = 0; i < 16; i++) {
            result[block + i] = outputBlock[i];
            previousBlock[i] = outputBlock[i];
        }
    }

    AES128_SetShowState(false);
    return result;
}

std::vector<uint8_t> CBC_Decrypt(const std::vector<uint8_t>& cipher, const uint8_t* key, const uint8_t* iv, bool showState) {
    if (cipher.size() % 16 != 0) {
        throw std::runtime_error("Длина шифртекста должна быть кратна 16 байтам");
    }

    uint8_t roundKeys[176];
    AES128_KeyExpansion(key, roundKeys);
    AES128_SetShowState(showState);

    if (showState) {
        AES128_PrintRoundKeys(roundKeys);
    }

    std::vector<uint8_t> result(cipher.size());

    uint8_t previousBlock[16];
    for (int i = 0; i < 16; i++) previousBlock[i] = iv[i];

    for (size_t block = 0; block < cipher.size(); block += 16) {
        uint8_t decryptedBlock[16];
        uint8_t currentCipherBlock[16];

        for (int i = 0; i < 16; i++) {
            currentCipherBlock[i] = cipher[block + i];
        }

        AES128_DecryptBlock(currentCipherBlock, roundKeys, decryptedBlock);

        for (int i = 0; i < 16; i++) {
            result[block + i] = decryptedBlock[i] ^ previousBlock[i];
            previousBlock[i] = currentCipherBlock[i];
        }
    }

    AES128_SetShowState(false);
    RemovePadding(result);
    return result;
}
