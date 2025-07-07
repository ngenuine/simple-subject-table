#include "Common/Types.h"

#include <QHash>

using subject::Field;

QString subject::ToString(Field field)
{
    switch (field)
    {
    case Field::ID:
        return "ID";
    case Field::AGE:
        return "Возраст";
    case Field::EXP:
        return "Опыт";
    case Field::GENDER:
        return "Пол";
    case Field::LAST_NAME:
        return "Фамилия";
    case Field::FIRST_NAME:
        return "Имя";
    case Field::MID_NAME:
        return "Отчество";
    case Field::PHONE:
        return "Телефон";
    case Field::CITIZENSHIP:
        return "Гражданство";
    default:
        return "---";
    }

    return "#FIELD";
}

uint subject::hhash(const subject::User& key, uint seed)
{
    return qHashMulti(
        seed, key.age, key.experience, key.gender, key.lastName, key.firstName, key.middleName, key.phoneNumber,
        key.citizenship);
}
