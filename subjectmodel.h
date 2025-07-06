#ifndef SUBJECTMODEL_H
#define SUBJECTMODEL_H

#include "Types.h"

#include <QAbstractTableModel>
#include <QObject>

class SubjectModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit SubjectModel(QObject *parent = nullptr);

    int      rowCount(const QModelIndex& parent) const override;
    int      columnCount(const QModelIndex& parent) const override;
    QVariant data(const QModelIndex& index, int role) const override;

private:
    std::vector<subject::User> m_users;
};

#endif // SUBJECTMODEL_H
