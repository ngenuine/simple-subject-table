#include "Types.h"

using subject::Field;

QString ToString(Field field)
{
    switch (field)
    {
    case Field::ID:
        return "id";
    case Field::AGE:
        return "Возраст";
    case Field::EXP:
        return "Опыт";
    case Field::LAST_NAME:
        return "Фамилия";
    case Field::FIRST_NAME:
        return "Имя";
    case Field::MID_NAME:
        return "Отчество";
    case Field::GENDER:
        return "Пол";
    case Field::PHONE:
        return "Телефон";
    case Field::CITIZENSHIP:
        return "Гражданство";
    case Field::UNKNOWN:
        return "Неизвестно";
    default:
        return "default";
    }

    return "error";
}
