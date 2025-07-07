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
        QByteArray toWrite;

        uint64_t count = 0;
        for (const auto& user : m_pModel->GetData())
        {
            QByteArray ba = Serialize(user);
            toWrite.append(ba);
            ++count;
        }
        std::ofstream out(fileName.toStdString(), std::ios::binary);  // tostdwstring попробовать
        out.write(reinterpret_cast<char*>(&count), sizeof(count));
        out.write(toWrite.constData(), toWrite.size());
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
        std::ifstream in(fileName.toStdString(), std::ios::binary);  // tostdwstring попробовать

        std::vector<subject::User> users;
        uint64_t                   count = 0;
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
