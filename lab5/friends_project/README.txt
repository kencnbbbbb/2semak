Многофайловый проект на C++

Тема:
Автоматизированная система учета дружеских связей между людьми.
Вариант 1. Комбинация контейнеров.

Файлы проекта:
1) main.cpp — главный файл программы, ввод команд и вывод результатов.
2) SocialNetwork.h — описание класса SocialNetwork.
3) SocialNetwork.cpp — реализация методов класса SocialNetwork.

Команды:
FRIENDS i j
Записывает i и j как друзей.
Если они уже друзья, выводится сообщение, что они уже друзья.
Если имена одинаковые, отдельное сообщение не выводится, но QUESTION i i дает Yes.

COUNT i
Подсчет количества друзей i.

QUESTION i j
Проверка, дружат ли i и j.
Результат: Yes или No.

Компиляция:
g++ main.cpp SocialNetwork.cpp -o friends

Запуск на macOS/Linux:
./friends

Запуск на Windows:
friends.exe

Пример ввода:
9
FRIENDS Peter Goward
FRIENDS Goward Peter
FRIENDS Peter Peter
FRIENDS Goward Sally
COUNT Goward
COUNT Justin
QUESTION Goward Peter
QUESTION Peter Peter
QUESTION Justin Jenny

Ожидаемый вывод совпадает с примером из задания.
