#include "widget.h"
#include "ui_widget.h"

#include "Crc32/crc32.h"
#include "Dialog/adduser.h"
#include "Dialog/seed.h"
#include "Model/subjectmodel.h"
#include "Serialization/Serialization.h"

#include <QDialog>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>

#include <fstream>

Widget::Widget(QWidget* parent)
    : QWidget(parent, Qt::Window | Qt::WindowTitleHint | Qt::WindowCloseButtonHint)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    m_pModel = new SubjectModel(this);
    ui->tableView->setModel(m_pModel);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_addUserBtn_clicked()
{
    AddUser dialog;
    int     result = dialog.exec();
    if (result == QDialog::Accepted)
    {
        m_pModel->addRow(dialog.User());
    }
}

void Widget::on_writeFileBtn_clicked()
{
    Seed dialog;
    int  result = dialog.exec();
    if (result == QDialog::Accepted)
    {
        uint8_t seed     = dialog.GetSeed();
        QString fileName = QFileDialog::getSaveFileName(
            this, "Сохранить", QDir::homePath() + "/data.bin", "Файл данных (*.bin);;Все файлы (*)");
        QByteArray toWriteData;

        uint64_t count = 0;
        for (const auto& user : m_pModel->GetData())
        {
            QByteArray ba = Serialize(user);
            toWriteData.append(ba);
            ++count;
        }
        QByteArray toWriteCount(reinterpret_cast<char*>(&count), sizeof(count));

        QByteArray result;
        result.append(toWriteCount);
        result.append(toWriteData);

        XorBuffer(result, seed);

        uint32_t crc32    = calculateCRC32(result);
        QString  crcLabel = QString("0x%1").arg(crc32, 8, 16, QLatin1Char('0'));

        ui->crcLabel->setText(ui->crcLabel->text() + " " + crcLabel);

        std::ofstream out(fileName.toStdString(), std::ios::binary);
        out.write(result.constData(), result.size());
    }
}

void Widget::on_checkFileBtn_clicked()
{
    Seed dialog;
    int  result = dialog.exec();
    if (result == QDialog::Accepted)
    {
        uint8_t seed = dialog.GetSeed();
        QString fileName =
            QFileDialog::getOpenFileName(this, tr("Открыть"), QDir::homePath(), "Файл данных (*.bin);;Все файлы (*)");
        std::ifstream in(fileName.toStdString(), std::ios::binary);

        QByteArray countBa(sizeof(uint64_t), Qt::Uninitialized);
        in.read(countBa.data(), countBa.size());
        XorBuffer(countBa, seed);
        uint64_t             count = 0;
        const unsigned char* bytes = reinterpret_cast<const uchar*>(countBa.constData());
        for (int i = 0; i < sizeof(uint64_t); ++i)
            count |= static_cast<uint64_t>(bytes[i]) << (i * 8);

        if (count > 1000)  // Искусственное ограничение количества пользователей
        {
            // Если seed введен неверно, то count может стать очень большим и программа зависнет
            QMessageBox::critical(nullptr, "Ошибка подсчета пользователей", "Возможно, шифрующее число неверно");
            m_pModel->SetData(std::vector<subject::User>{});
            return;
        }

        auto remainingSize = [this, seed](std::istream& in)
        {
            std::streampos currentPos = in.tellg();
            in.seekg(0, std::ios::end);
            std::streamsize endPos        = in.tellg();
            std::streamsize remainingSize = endPos - currentPos;
            in.seekg(currentPos);

            return remainingSize;
        }(in);
        QByteArray ba(remainingSize, Qt::Uninitialized);
        in.read(ba.data(), ba.size());
        XorBuffer(ba, seed);

        std::istringstream iss(std::string(ba.constData(), ba.size()), std::ios::binary);

        std::vector<subject::User> users;
        while (count-- > 0)
        {
            subject::User user;
            Deserialize(iss, user);
            users.push_back(std::move(user));
        }

        m_pModel->SetData(users);
    }
}
