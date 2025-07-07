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

char Seed::GetSeed() const
{
    return m_seed;
}

void Seed::on_acceptBtn_clicked()
{
    m_seed = ui->seedBox->value() % 256;
    accept();
}

void Seed::on_rejectBtn_clicked()
{
    m_seed = 0;
    reject();
}
