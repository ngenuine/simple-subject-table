#ifndef TYPES_H
#define TYPES_H

#include <QString>
#include <cstdint>

enum class Gender : uint8_t
{
    MALE = 0,
    FEMALE
};

struct User
{
    uint64_t id;           // Уникальный идентификатор.
    uint8_t  age;          // Возраст.
    uint8_t  experience;   // Опыт.
    Gender   gender;       // Пол.
    QString  lastName;     // Фамилия.
    QString  firstName;    // Имя.
    QString  middleName;   // Отчество.
    QString  phoneNumber;  // Номер телефона.
    QString  citizenship;  // Гражданство.
};

#endif  // TYPES_H
