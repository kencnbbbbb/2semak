#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <openssl/evp.h>
#include <openssl/rand.h>

using namespace std;

void saveFile(const string& name, const vector<unsigned char>& data) {
    ofstream file(name, ios::binary);
    file.write((char*)data.data(), data.size());
}

vector<unsigned char> readFile(const string& name) {
    ifstream file(name, ios::binary);
    return vector<unsigned char>((istreambuf_iterator<char>(file)), {});
}

vector<unsigned char> aesEncrypt(
    const vector<unsigned char>& text,
    const vector<unsigned char>& key,
    const vector<unsigned char>& iv
) {
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();

    vector<unsigned char> cipher(text.size() + 16);
    int len = 0;
    int cipherLen = 0;

    EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), nullptr, key.data(), iv.data());

    EVP_EncryptUpdate(ctx, cipher.data(), &len, text.data(), text.size());
    cipherLen = len;

    EVP_EncryptFinal_ex(ctx, cipher.data() + len, &len);
    cipherLen += len;

    cipher.resize(cipherLen);
    EVP_CIPHER_CTX_free(ctx);

    return cipher;
}

vector<unsigned char> aesDecrypt(
    const vector<unsigned char>& cipher,
    const vector<unsigned char>& key,
    const vector<unsigned char>& iv
) {
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();

    vector<unsigned char> text(cipher.size());
    int len = 0;
    int textLen = 0;

    EVP_DecryptInit_ex(ctx, EVP_aes_128_cbc(), nullptr, key.data(), iv.data());

    EVP_DecryptUpdate(ctx, text.data(), &len, cipher.data(), cipher.size());
    textLen = len;

    EVP_DecryptFinal_ex(ctx, text.data() + len, &len);
    textLen += len;

    text.resize(textLen);
    EVP_CIPHER_CTX_free(ctx);

    return text;
}

int main() {
    setlocale(LC_ALL, "Russian");

    int choice;

    cout << "AES-128 CBC\n";
    cout << "1 - Зашифровать текст\n";
    cout << "2 - Расшифровать текст\n";
    cout << "Выбор: ";
    cin >> choice;
    cin.ignore();

    if (choice == 1) {
        string input;

        cout << "Введите исходный текст: ";
        getline(cin, input);

        vector<unsigned char> text(input.begin(), input.end());

        vector<unsigned char> key(16);
        vector<unsigned char> iv(16);

        RAND_bytes(key.data(), 16);
        RAND_bytes(iv.data(), 16);

        vector<unsigned char> cipher = aesEncrypt(text, key, iv);

        saveFile("key.bin", key);
        saveFile("iv.bin", iv);
        saveFile("cipher.bin", cipher);

        cout << "Текст зашифрован.\n";
        cout << "Ключ записан в key.bin\n";
        cout << "Вектор IV записан в iv.bin\n";
        cout << "Шифртекст записан в cipher.bin\n";
    }
    else if (choice == 2) {
        vector<unsigned char> key = readFile("key.bin");
        vector<unsigned char> iv = readFile("iv.bin");
        vector<unsigned char> cipher = readFile("cipher.bin");

        vector<unsigned char> text = aesDecrypt(cipher, key, iv);

        string result(text.begin(), text.end());

        cout << "Расшифрованный текст:\n";
        cout << result << endl;
    }
    else {
        cout << "Неверный выбор.\n";
    }

    return 0;
}