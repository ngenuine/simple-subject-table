#include "adduser.h"
#include "ui_adduser.h"

#include "Types.h"

AddUser::AddUser(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::AddUser)
{
    ui->setupUi(this);
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
