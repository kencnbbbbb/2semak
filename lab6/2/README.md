# AES128 CBC — многофайловый проект C++

Проект реализует шифрование и расшифрование AES128 в режиме CBC.

## Структура проекта

```text
AES128_CBC_Project_No_Makefile/
├── src/
│   ├── main.cpp
│   ├── aes.cpp
│   ├── cbc.cpp
│   └── utils.cpp
│
├── include/
│   ├── aes.h
│   ├── cbc.h
│   └── utils.h
│
└── README.md
```

## Запуск в VS Code без Makefile

1. Открой папку проекта через:

```text
File → Open Folder...
```

2. Открой терминал:

```text
Terminal → New Terminal
```

3. Собери проект одной командой.

### Windows MinGW

```bash
g++ -std=c++17 src/main.cpp src/aes.cpp src/cbc.cpp src/utils.cpp -Iinclude -o aes_cbc.exe
```

Запуск:

```bash
./aes_cbc.exe
```

или:

```bash
aes_cbc.exe
```

### macOS / Linux

```bash
g++ -std=c++17 src/main.cpp src/aes.cpp src/cbc.cpp src/utils.cpp -Iinclude -o aes_cbc
```

Запуск:

```bash
./aes_cbc
```

## Что делает программа

Программа позволяет:

1. Зашифровать исходный текст AES128 CBC.
2. Расшифровать зашифрованный текст обратно в исходный.
3. Сгенерировать случайный ключ.
4. Сохранить ключ в файл `key.txt`.
5. Вывести IV, Round Keys и промежуточные состояния State.
6. Работать с русским и английским текстом в UTF-8.

## Пример компиляции вручную

```bash
g++ -std=c++17 src/main.cpp src/aes.cpp src/cbc.cpp src/utils.cpp -Iinclude -o aes_cbc
```

После этого запускается готовый файл программы.
