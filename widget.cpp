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
#include <sstream>

Widget::Widget(QWidget* parent)
    : QWidget(parent, Qt::Window | Qt::WindowTitleHint | Qt::WindowCloseButtonHint)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setFixedSize(1000, 500);

    m_pModel = new SubjectModel(this);
    ui->tableView->setModel(m_pModel);

    connect(m_pModel, &QAbstractItemModel::dataChanged, this, [this]() { ui->tableView->resizeColumnsToContents(); });
    connect(m_pModel, &QAbstractItemModel::modelReset, this, [this]() { ui->tableView->resizeColumnsToContents(); });

    // Выделение строк полностью.
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->addUserBtn->setToolTip("При выделенной строке диалог заполнится ее значениями");
    ui->addUserBtn->setToolTipDuration(2000);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_addUserBtn_clicked()
{
    int                      result  = QDialog::Rejected;
    std::shared_ptr<AddUser> pDialog = nullptr;

    subject::User   user;
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedRows();
    if (!selectedIndexes.isEmpty())
    {
        auto index = selectedIndexes.at(0).row();
        if (index >= m_pModel->GetData().size())
            return;
        user = m_pModel->GetData().at(index);
    }

    pDialog = std::make_shared<AddUser>(user);

    if (pDialog && pDialog->exec() == QDialog::Accepted)
    {
        m_pModel->addRow(pDialog->User());
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
            this, "Сохранить", QDir::homePath() + "/data.bin", "Файл данных (*.bin);;КС (*.crc)");
        QByteArray toWriteData;

        if (fileName.isEmpty())
            return;

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

        uint32_t crc32 = calculateCRC32(result);

        ui->crcLabel->setText("crc: ");
        ui->crcLabel->setText(ui->crcLabel->text() + " " + QString::number(crc32));

        QString crcFileName =
            QFileInfo(fileName).absolutePath() + "/" + QFileInfo(fileName).completeBaseName() + ".crc";
        std::ofstream(crcFileName.toStdString()) << crc32;

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
            QFileDialog::getOpenFileName(this, tr("Открыть"), QDir::homePath(), "Файл данных (*.bin);;КС (*.crc)");
        if (fileName.isEmpty())
            return;

        std::ifstream in(fileName.toStdString(), std::ios::binary);
        auto          fileSize = [](std::istream& in)
        {
            std::streampos currentPos = in.tellg();
            in.seekg(0, std::ios::end);
            std::streamsize endPos = in.tellg();
            std::streamsize size   = endPos - currentPos;
            in.seekg(currentPos);

            return size;
        }(in);

        QByteArray fullFileBa(fileSize, Qt::Uninitialized);
        in.read(fullFileBa.data(), fullFileBa.size());

        QString crcFileName =
            QFileInfo(fileName).absolutePath() + "/" + QFileInfo(fileName).completeBaseName() + ".crc";
        if (!QFileInfo(fileName).exists())
        {
            QMessageBox::critical(nullptr, "Ошибка", "Соответствующий файл с контрольной суммой не найден");
            return;
        }

        uint32_t crc32;
        std::ifstream(crcFileName.toStdString()) >> crc32;
        if (crc32 != calculateCRC32(fullFileBa))
        {
            QMessageBox::critical(nullptr, "Ошибка", "Неверная контрольная сумма. Файл поврежден");
            return;
        }

        ui->crcLabel->setText("crc: ");
        ui->crcLabel->setText(ui->crcLabel->text() + " " + QString::number(crc32));

        XorBuffer(fullFileBa, seed);

        // copy-on-write (не копии)
        QByteArray countBa(fullFileBa.data(), sizeof(uint64_t));
        QByteArray dataBa(fullFileBa.data() + sizeof(uint64_t), fullFileBa.size() - sizeof(uint64_t));

        uint64_t count = 0;
        for (int i = 0; i < sizeof(uint64_t); ++i)
            count |= static_cast<uint64_t>(static_cast<unsigned char>(countBa[i])) << (i * 8);

        if (count > 1000)
        {
            /* Искусственное ограничение количества пользователей если seed введен неверно, то count может стать очень
             * большим и программа зависнет, т.к. count используется в дальнейшей в цикле */
            QMessageBox::critical(nullptr, "Ошибка подсчета пользователей", "Возможно, шифрующее число неверно");
            m_pModel->SetData(std::vector<subject::User>{});
            return;
        }

        std::istringstream iss(std::string(dataBa.constData(), dataBa.size()), std::ios::binary);

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

void Widget::on_deleteUser_clicked()
{
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedRows();
    for (const auto& index : selectedIndexes)
        m_pModel->removeRow(index.row());
}
