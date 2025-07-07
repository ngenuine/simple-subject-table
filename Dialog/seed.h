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
    char GetSeed() const;

private slots:
    void on_acceptBtn_clicked();

    void on_rejectBtn_clicked();

private:
    Ui::Seed* ui;
    char      m_seed;
};

#endif  // SEED_H
