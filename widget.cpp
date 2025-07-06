#include "widget.h"
#include "./ui_widget.h"

#include "subjectmodel.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
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
