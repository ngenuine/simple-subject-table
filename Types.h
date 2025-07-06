#ifndef TYPES_H
#define TYPES_H

#include <QString>
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

enum class Field : uint8_t
{
    UNKNOWN = 0,
    ID,
    AGE,
    EXP,
    LAST_NAME,
    FIRST_NAME,
    MID_NAME,
    GENDER,
    PHONE,
    CITIZENSHIP
};

const std::array<Field, 9> userFields{Field::ID,        Field::AGE,        Field::EXP,
                                      Field::LAST_NAME, Field::FIRST_NAME, Field::MID_NAME,
                                      Field::GENDER,    Field::PHONE,      Field::CITIZENSHIP};

QString ToString(Field field);

}  // namespace subject

#endif  // TYPES_H
