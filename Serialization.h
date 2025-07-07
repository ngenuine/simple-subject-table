#ifndef SERIALIZATION_H
#define SERIALIZATION_H

#include "Types.h"

#include <QString>
#include <cstdint>
#include <istream>
#include <ostream>

using subject::User;

template<typename T>
void Serialize(T num, std::ostream& out)
{
    static_assert(std::is_arithmetic_v<T> || std::is_enum_v<T>, "Serialize<T>: T должен быть числом или enum");

    uint8_t size = sizeof(num);
    out.write(reinterpret_cast<const char*>(&num), size);
}
void       Serialize(const QString& str, std::ostream& out);
void       Serialize(const User& user, std::ostream& out);
QByteArray Serialize(const User& user);

template<typename T>
void Deserialize(std::istream& in, T& num)
{
    static_assert(std::is_arithmetic_v<T> || std::is_enum_v<T>, "Serialize<T>: T должен быть числом или enum");

    uint8_t size = sizeof(num);
    in.read(reinterpret_cast<char*>(&num), size);
}
void Deserialize(std::istream& in, QString& str);
void Deserialize(std::istream& in, User& user);
User Deserialize(const QByteArray& ba);

#endif  // SERIALIZATION_H
