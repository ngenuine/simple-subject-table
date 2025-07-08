#ifndef TYPES_H
#define TYPES_H

#include <QHash>
#include <QString>

#include <array>
#include <cstdint>

enum class Gender : uint8_t
{
    MALE = 0,
    FEMALE
};

namespace subject
{

struct User
{
    uint64_t id         = 0;               // Уникальный идентификатор.
    uint8_t  age        = 7;               // Возраст.
    uint8_t  experience = 0;               // Опыт.
    Gender   gender     = Gender::FEMALE;  // Пол.

    QString  lastName;     // Фамилия.
    QString  firstName;    // Имя.
    QString  middleName;   // Отчество.

    QString  phoneNumber;  // Номер телефона.
    QString  citizenship;  // Гражданство.
};

enum class Field : uint8_t
{
    ID = 0,
    AGE,
    EXP,
    GENDER,

    LAST_NAME,
    FIRST_NAME,
    MID_NAME,

    PHONE,
    CITIZENSHIP
};

const std::array<Field, 9> userFields{Field::ID,        Field::AGE,        Field::EXP,
                                      Field::LAST_NAME, Field::FIRST_NAME, Field::MID_NAME,
                                      Field::GENDER,    Field::PHONE,      Field::CITIZENSHIP};

QString ToString(Field field);

uint hhash(const User& key, uint seed = 0);

}  // namespace subject

#endif  // TYPES_H
