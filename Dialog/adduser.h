#ifndef ADDUSER_H
#define ADDUSER_H

#include "Common/Types.h"

#include <QDialog>

namespace Ui
{
class AddUser;
}

class AddUser : public QDialog
{
    Q_OBJECT

public:
    explicit AddUser(QWidget* parent = nullptr);
    ~AddUser();

    subject::User User() const;

private slots:
    void on_applyBtn_clicked();

    void on_rejectBtn_clicked();

private:
    Ui::AddUser*  ui;
    subject::User m_user;
};

#endif  // ADDUSER_H
