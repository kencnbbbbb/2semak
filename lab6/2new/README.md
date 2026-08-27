# AES128 CBC. Шифрование и расшифрование текста

Многофайловый проект C++ без OpenSSL и без Makefile.

## Файлы

```text
src/main.cpp
src/aes.cpp
src/cbc.cpp
src/utils.cpp
include/aes.h
include/cbc.h
include/utils.h
```

## Сборка в VS Code

Открой папку проекта, затем в терминале выполни:

```bash
g++ -std=c++17 src/main.cpp src/aes.cpp src/cbc.cpp src/utils.cpp -Iinclude -o aes_cbc
```

## Запуск

Mac/Linux:

```bash
./aes_cbc
```

Windows:

```bash
./aes_cbc.exe
```

## Что умеет программа

1. Шифрует русский или английский текст в AES128 CBC.
2. Генерирует случайный ключ AES128 и IV.
3. Сохраняет ключ в файл `key.txt`.
4. Выводит HEX-шифртекст.
5. После шифрования дополнительно реально расшифровывает полученный HEX и выводит расшифрованный текст.
6. Может отдельно расшифровать HEX-текст по ключу и IV.
