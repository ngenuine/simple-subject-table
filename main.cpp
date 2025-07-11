#include "widget.h"

#include "Common/Types.h"
#include "Serialization/Serialization.h"

#include <QApplication>
#include <QDebug>

#include <fstream>

void test();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

    test();

    w.show();
    return a.exec();
}

void test()
{
    {
        subject::User user1;
        user1.id          = 25734;
        user1.age         = 50;
        user1.experience  = 30;
        user1.gender      = Gender::FEMALE;
        user1.lastName    = "Фамилия_1";
        user1.firstName   = "Имя_1";
        user1.middleName  = "Отчество_1";
        user1.phoneNumber = "+7-292-467-32-05";
        user1.citizenship = "Австралия";

        subject::User user2;
        user2.id          = 1234;
        user2.age         = 25;
        user2.experience  = 6;
        user2.gender      = Gender::MALE;
        user2.lastName    = "Family_Two";
        user2.firstName   = "Имя_2";
        user2.middleName  = "Отчество_2";
        user2.phoneNumber = "8-313-000-92-15";
        user2.citizenship = "Новая Zeland";

        std::ofstream out("test.bin", std::ios::binary);
        uint64_t      count = 2;  // Количество записей.
        out.write(reinterpret_cast<char*>(&count), sizeof(count));
        Serialize(user1, out);
        Serialize(user2, out);
    }

    subject::User user1;
    subject::User user2;
    {
        uint64_t      count;
        std::ifstream in("test.bin", std::ios::binary);
        in.read(reinterpret_cast<char*>(&count), sizeof(count));
        Deserialize(in, user1);
        Deserialize(in, user2);
    }

    qDebug() << "[[[ main.cpp::test()\n";

    qDebug() << user1.id << " " << user1.age << " " << user1.experience << " "
             << (user1.gender == Gender::FEMALE ? "FEMALE" : "MALE") << " " << user1.lastName << " " << user1.firstName
             << " " << user1.middleName << " " << user1.phoneNumber << " " << user1.citizenship;

    qDebug() << user2.id << " " << user2.age << " " << user2.experience << " "
             << (user2.gender == Gender::FEMALE ? "FEMALE" : "MALE") << " " << user2.lastName << " " << user2.firstName
             << " " << user2.middleName << " " << user2.phoneNumber << " " << user2.citizenship;

    qDebug() << "\nmain.cpp::test() ]]]";
}
