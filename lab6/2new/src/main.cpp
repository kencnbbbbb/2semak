#include "cbc.h"
#include "utils.h"
#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <stdexcept>

using namespace std;

static void CopyVectorToBlock(const vector<uint8_t>& source, uint8_t block[16], const string& name) {
    if (source.size() != 16) {
        throw runtime_error(name + " должен быть ровно 16 байт, то есть 32 HEX-символа");
    }

    for (int i = 0; i < 16; i++) {
        block[i] = source[i];
    }
}

int main() {
    setlocale(LC_ALL, "");

    cout << "доп задача: AES128 CBC. Шифрование и расшифрование текста" << endl;
    cout << "1 - зашифровать текст" << endl;
    cout << "2 - расшифровать HEX-текст" << endl;
    cout << "Выберите режим: ";

    int mode;
    cin >> mode;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Показывать промежуточные State? (1 - да, 0 - нет): ";
    int showStateValue;
    cin >> showStateValue;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    bool showState = (showStateValue == 1);

    try {
        if (mode == 1) {
            string text;
            uint8_t key[16];
            uint8_t iv[16];

            cout << "Введите исходный текст на русском или английском: ";
            getline(cin, text);

            GenerateRandomBytes(key, 16);
            GenerateRandomBytes(iv, 16);
            SaveKeyToFile(key, "key.txt");

            vector<uint8_t> plainBytes = TextToBytes(text);
            vector<uint8_t> cipherBytes = CBC_Encrypt(plainBytes, key, iv, showState);
            string cipherHex = BytesToHex(cipherBytes);

            cout << "Случайный ключ AES128: " << BytesToHex(vector<uint8_t>(key, key + 16)) << endl;
            cout << "Вектор инициализации IV: " << BytesToHex(vector<uint8_t>(iv, iv + 16)) << endl;
            cout << "Ключ записан в файл key.txt" << endl;
            cout << "Зашифрованный текст HEX: " << cipherHex << endl;

            // Проверка делается честно: сначала берется HEX-шифртекст,
            // затем он обратно расшифровывается через AES128 CBC.
            vector<uint8_t> cipherBytesFromHex = HexToBytes(cipherHex);
            vector<uint8_t> decryptedBytes = CBC_Decrypt(cipherBytesFromHex, key, iv, false);

            cout << "Расшифрованный текст: " << BytesToText(decryptedBytes) << endl;
            cout << "Для расшифрования сохраните HEX, ключ из key.txt и IV." << endl;
        }
        else if (mode == 2) {
            string cipherHex;
            string keyHex;
            string ivHex;
            uint8_t key[16];
            uint8_t iv[16];

            cout << "Введите зашифрованный HEX-текст: ";
            getline(cin, cipherHex);

            cout << "Введите ключ AES128 из key.txt: ";
            getline(cin, keyHex);

            cout << "Введите IV: ";
            getline(cin, ivHex);

            vector<uint8_t> cipherBytes = HexToBytes(cipherHex);
            vector<uint8_t> keyBytes = HexToBytes(keyHex);
            vector<uint8_t> ivBytes = HexToBytes(ivHex);

            CopyVectorToBlock(keyBytes, key, "Ключ AES128");
            CopyVectorToBlock(ivBytes, iv, "IV");

            vector<uint8_t> decryptedBytes = CBC_Decrypt(cipherBytes, key, iv, showState);
            cout << "Расшифрованный текст: " << BytesToText(decryptedBytes) << endl;
        }
        else {
            cout << "Такого режима нет." << endl;
        }
    }
    catch (const exception& error) {
        cout << "Ошибка: " << error.what() << endl;
    }

    return 0;
}
