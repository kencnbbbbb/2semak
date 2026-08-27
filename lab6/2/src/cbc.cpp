#include "cbc.h"
#include "utils.h"
#include <stdexcept>

std::vector<Byte> pkcs7Pad(const std::vector<Byte>& data) {
    std::vector<Byte> result = data;
    int pad = 16 - (int)(result.size() % 16);
    if (pad == 0) pad = 16;
    for (int i = 0; i < pad; ++i) result.push_back((Byte)pad);
    return result;
}

std::vector<Byte> pkcs7Unpad(const std::vector<Byte>& data) {
    if (data.empty() || data.size() % 16 != 0) throw std::runtime_error("Ошибка PKCS7: неверный размер данных");
    Byte pad = data.back();
    if (pad == 0 || pad > 16 || pad > data.size()) throw std::runtime_error("Ошибка PKCS7: неверное заполнение");
    for (int i = 0; i < pad; ++i) {
        if (data[data.size() - 1 - i] != pad) throw std::runtime_error("Ошибка PKCS7: поврежденное заполнение");
    }
    return std::vector<Byte>(data.begin(), data.end() - pad);
}

std::vector<Byte> encryptCBC(const std::string& text, const Block& key, const Block& iv, bool verbose) {
    AES128 aes(key, verbose);
    if (verbose) aes.printRoundKeys();

    std::vector<Byte> input(text.begin(), text.end());
    input = pkcs7Pad(input);

    std::vector<Byte> cipher;
    Block previous = iv;

    for (size_t pos = 0; pos < input.size(); pos += 16) {
        Block block{};
        for (int i = 0; i < 16; ++i) block[i] = input[pos + i] ^ previous[i];
        if (verbose) printBlock("Блок после XOR с предыдущим CBC-блоком", block);
        Block encrypted = aes.encryptBlock(block, (int)(pos / 16 + 1));
        cipher.insert(cipher.end(), encrypted.begin(), encrypted.end());
        previous = encrypted;
    }

    return cipher;
}

std::string decryptCBC(const std::vector<Byte>& cipher, const Block& key, const Block& iv, bool verbose) {
    if (cipher.empty() || cipher.size() % 16 != 0) throw std::runtime_error("Шифртекст должен быть кратен 16 байтам");

    AES128 aes(key, verbose);
    if (verbose) aes.printRoundKeys();

    std::vector<Byte> output;
    Block previous = iv;

    for (size_t pos = 0; pos < cipher.size(); pos += 16) {
        Block block{};
        for (int i = 0; i < 16; ++i) block[i] = cipher[pos + i];
        Block decrypted = aes.decryptBlock(block, (int)(pos / 16 + 1));
        for (int i = 0; i < 16; ++i) decrypted[i] ^= previous[i];
        if (verbose) printBlock("Блок после обратного XOR CBC", decrypted);
        output.insert(output.end(), decrypted.begin(), decrypted.end());
        previous = block;
    }

    output = pkcs7Unpad(output);
    return std::string(output.begin(), output.end());
}
