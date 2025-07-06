#include "Serialization.h"

#include <sstream>

void Serialize(const QString& str, std::ostream& out)
{
    QByteArray ba   = str.toUtf8();
    uint8_t    size = ba.size();
    out.write(reinterpret_cast<const char*>(&size), sizeof(size));  // Записываем размер последующей строки.
    out.write(ba.constData(), size);                                // Записываем саму строку.
}

void Serialize(const subject::User& user, std::ostream& out)
{
    Serialize(user.id, out);
    Serialize(user.age, out);
    Serialize(user.experience, out);
    Serialize(user.gender, out);
    Serialize(user.lastName, out);
    Serialize(user.firstName, out);
    Serialize(user.middleName, out);
    Serialize(user.phoneNumber, out);
    Serialize(user.citizenship, out);
}

QByteArray Serialize(const subject::User& user)
{
    std::ostringstream out(std::ios::binary);
    Serialize(user, out);

    const std::string& data = out.str();
    return QByteArray::fromRawData(data.data(), data.size());
}

void Deserialize(std::istream& in, QString& str)
{
    uint8_t size;
    in.read(reinterpret_cast<char*>(&size), sizeof(size));  // Читаем размер последующей строки.

    QByteArray ba(size, 0);
    in.read(ba.data(), size);  // Читаем саму строку.

    str = QString::fromUtf8(ba);
}

void Deserialize(std::istream& in, subject::User& user)
{
    Deserialize(in, user.id);
    Deserialize(in, user.age);
    Deserialize(in, user.experience);
    Deserialize(in, user.gender);
    Deserialize(in, user.lastName);
    Deserialize(in, user.firstName);
    Deserialize(in, user.middleName);
    Deserialize(in, user.phoneNumber);
    Deserialize(in, user.citizenship);
}

subject::User Deserialize(const QByteArray& ba)
{
    std::string        data(ba.constData(), ba.size());
    std::istringstream in(data, std::ios::binary);

    subject::User user;
    Deserialize(in, user);
    return std::move(user);
}
