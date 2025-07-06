#include "subjectmodel.h"
#include "Types.h"

#include <QVariant>

SubjectModel::SubjectModel(QObject *parent)
    : QAbstractTableModel{parent}
{}

int SubjectModel::rowCount(const QModelIndex& parent) const
{
    return m_users.size();
}

int SubjectModel::columnCount(const QModelIndex& parent) const
{
    return subject::userFields.size();
}

QVariant SubjectModel::data(const QModelIndex& index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        return QVariant("Ничего");
    }
    return QVariant();
}

void SubjectModel::addRow(const subject::User& rowData)
{}
