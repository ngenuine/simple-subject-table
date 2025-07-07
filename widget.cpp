#include "widget.h"
#include "./ui_widget.h"

#include "adduser.h"
#include "subjectmodel.h"

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
