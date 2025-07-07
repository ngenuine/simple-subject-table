#include "Dialog/adduser.h"
#include "ui_adduser.h"

#include "Common/Types.h"

AddUser::AddUser(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::AddUser)
{
    ui->setupUi(this);
}

AddUser::AddUser(subject::User user, QWidget* parent)
    : AddUser(parent)
{
    ui->ageSpin->setValue(user.age);
    ui->experienceSpin->setValue(user.experience);

    if (user.gender == Gender::MALE)
        ui->maleRadio->setChecked(true);
    else
        ui->femaleRadio->setChecked(true);

    ui->lastNameEdit->setText(user.lastName);
    ui->firstNameEdit->setText(user.firstName);
    ui->middleNameEdit->setText(user.middleName);
    ui->phoneEdit->setText(user.phoneNumber);
    ui->citizenshipEdit->setText(user.citizenship);
}

AddUser::~AddUser()
{
    delete ui;
}

subject::User AddUser::User() const
{
    return m_user;
}

void AddUser::on_applyBtn_clicked()
{
    m_user.age         = static_cast<uint8_t>(ui->ageSpin->value());
    m_user.experience  = static_cast<uint8_t>(ui->experienceSpin->value());
    m_user.gender      = ui->maleRadio->isChecked() ? Gender::MALE : Gender::FEMALE;
    m_user.lastName    = ui->lastNameEdit->text();
    m_user.firstName   = ui->firstNameEdit->text();
    m_user.middleName  = ui->middleNameEdit->text();
    m_user.phoneNumber = ui->phoneEdit->text();
    m_user.citizenship = ui->citizenshipEdit->text();

    m_user.id = subject::hhash(m_user);

    accept();
}

void AddUser::on_rejectBtn_clicked()
{
    m_user = subject::User{};
    reject();
}
