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
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    void addRow(const subject::User& rowData);

private:
    std::vector<subject::User> m_users;
};

#endif // SUBJECTMODEL_H
