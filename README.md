# simple-subject-table

## Сборка и запуск

- Скачать архив их этого репозитория, распаковать на компьютере.
- Открыть терминал в директории `simple-subject-table-main`
- Собрать проект
```
$ ls
CMakeLists.txt  Crc32   main.cpp  README.md      UI          widget.h
Common          Dialog  Model     Serialization  widget.cpp
$ mkdir build
$ cd build/
$ cmake .. && cmake --build .
```
- Запустить программу
```
$ ./bin/stc-assignment
```

## Использование

Программа представляет собой окно, в котором можно добавлять пользователей. Пользователи отображаются в виде таблицы.

Первым делом надо добавить пользователей при помощи кнопки "Добавить пользователя". Вылезет диалог, в котором можно заполнить поля.
Если выделить строку и снова нажать "Добавить пользователя", то диалог добавления пользователя будет предзаполненным.

Пользователей можно удалять, предварительно выбрав строку в таблице.

Когда таблица заполнена, ее можно выгрузить в файл, нажав "Записать в файл". При этом будет предлоджено ввести число, с помощью которого файл зашифруется.
Для загрузки пользователей из файла при помощи кнопки "Проверить файл" будет также предложено ввести число. Это число должно быть таким же, как ранее введенное при записи пользователей в файл.
При записи пользователей в файл генерируется еще один файл, содержащий контрольную сумму, вычисленную алгоритмом CRC32. Файл *.crc позволяет контролировать целостность данных в файле с пользователями.

При записи и чтении в правомм нижне углу окна программы отображается контрольная сумма актуальной таблицы, доступной для просмора пользователю.

## Ограничения

- Двух одинаковых пользователей добавить не удастся.
- После записи пользователей в файл, рядом с файлом генерируется второй файл, который содержит контрольную сумму. Если изменить один из файлов, загрузить пользователей в программу уже не получится.

## Технологии

- С++17
- Qt
- CMake
