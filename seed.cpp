#include "seed.h"
#include "ui_seed.h"

Seed::Seed(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::Seed)
    , m_seed(0)
{
    ui->setupUi(this);
}

Seed::~Seed()
{
    delete ui;
}
