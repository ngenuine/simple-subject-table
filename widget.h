#ifndef WIDGET_H
#define WIDGET_H

#include "Model/subjectmodel.h"

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:

    void on_addUserBtn_clicked();

    void on_writeFileBtn_clicked();

    void on_checkFileBtn_clicked();

private:
    Ui::Widget*   ui;
    SubjectModel* m_pModel = nullptr;

    void XorBuffer(QByteArray& ba, char key = 0) const;
};

inline void Widget::XorBuffer(QByteArray& ba, char key) const
{
    for (int i = 0; i < ba.size(); ++i)
        ba[i] ^= key;
}
#endif // WIDGET_H
