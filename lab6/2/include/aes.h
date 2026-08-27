#ifndef AES_H
#define AES_H

#include <array>
#include <cstdint>
#include <string>
#include <vector>

using Byte = uint8_t;
using Block = std::array<Byte, 16>;

class AES128 {
private:
    std::array<Byte, 176> roundKeys{};
    bool verbose;

    static Byte gmul(Byte a, Byte b);
    static Byte xtime(Byte x);

    void addRoundKey(Block& state, int round) const;
    void subBytes(Block& state) const;
    void invSubBytes(Block& state) const;
    void shiftRows(Block& state) const;
    void invShiftRows(Block& state) const;
    void mixColumns(Block& state) const;
    void invMixColumns(Block& state) const;
    void printState(const std::string& title, const Block& state) const;

public:
    AES128(const Block& key, bool showIntermediate = true);

    void expandKey(const Block& key);
    Block encryptBlock(Block input, int blockNumber = 1) const;
    Block decryptBlock(Block input, int blockNumber = 1) const;

    void printRoundKeys() const;
    const std::array<Byte, 176>& getRoundKeys() const;
};

#endif
