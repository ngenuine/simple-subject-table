#ifndef SEED_H
#define SEED_H

#include <QDialog>

namespace Ui
{
class Seed;
}

class Seed : public QDialog
{
    Q_OBJECT

public:
    explicit Seed(QWidget* parent = nullptr);
    ~Seed();

private:
    Ui::Seed* ui;
    char      m_seed;
};

#endif  // SEED_H
