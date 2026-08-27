#include "cbc.h"
#include "utils.h"
#include <iostream>
#include <limits>

int main() {
    try {
        std::cout << "AES128 CBC. Шифрование и расшифрование текста\n";
        std::cout << "1 - зашифровать текст\n";
        std::cout << "2 - расшифровать HEX-текст\n";
        std::cout << "Выберите режим: ";

        int mode;
        std::cin >> mode;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Показывать промежуточные State? (1 - да, 0 - нет): ";
        int show;
        std::cin >> show;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        bool verbose = (show == 1);

        if (mode == 1) {
            std::string text;
            std::cout << "Введите исходный текст на русском или английском: ";
            std::getline(std::cin, text);

            Block key = generateRandomBlock();
            Block iv = generateRandomBlock();
            saveKeyToFile(key, "key.txt");

            printBlock("Случайный ключ AES128", key);
            printBlock("Вектор инициализации IV", iv);
            std::cout << "Ключ записан в файл key.txt\n";

            std::vector<Byte> cipher = encryptCBC(text, key, iv, verbose);
            printBytes("Зашифрованный текст HEX", cipher);
            std::cout << "Для расшифрования сохраните HEX, ключ из key.txt и IV.\n";
        }
        else if (mode == 2) {
            std::string hexCipher, hexKey, hexIv;

            std::cout << "Введите зашифрованный текст HEX: ";
            std::getline(std::cin, hexCipher);
            std::cout << "Введите ключ HEX из key.txt: ";
            std::getline(std::cin, hexKey);
            std::cout << "Введите IV HEX: ";
            std::getline(std::cin, hexIv);

            std::vector<Byte> keyBytes = hexToBytes(hexKey);
            std::vector<Byte> ivBytes = hexToBytes(hexIv);
            if (keyBytes.size() != 16 || ivBytes.size() != 16) {
                std::cout << "Ошибка: ключ и IV должны быть по 16 байт, то есть 32 HEX-символа.\n";
                return 1;
            }

            Block key{}, iv{};
            for (int i = 0; i < 16; ++i) {
                key[i] = keyBytes[i];
                iv[i] = ivBytes[i];
            }

            std::vector<Byte> cipher = hexToBytes(hexCipher);
            std::string plain = decryptCBC(cipher, key, iv, verbose);
            std::cout << "Расшифрованный исходный текст: " << plain << std::endl;
        }
        else {
            std::cout << "Такого режима нет.\n";
        }
    }
    catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
