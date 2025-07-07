#include "widget.h"
#include "./ui_widget.h"

#include "Serialization.h"
#include "adduser.h"
#include "seed.h"
#include "subjectmodel.h"

#include <QDialog>
#include <QDir>
#include <QFileDialog>

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
        uint64_t count = 0;

        std::vector<subject::User> users;

        in.read(reinterpret_cast<char*>(&count), sizeof(count));
        while (count-- > 0)
        {
            subject::User user;
            Deserialize(in, user);
            users.push_back(std::move(user));
        }

        m_pModel->SetData(users);
    }
}
