#include "Model/subjectmodel.h"
#include "Common/Types.h"

#include <QMessageBox>
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
    using subject::Field;
    if (role == Qt::DisplayRole)
    {
        if (index.row() >= m_users.size())
            return QVariant("Out of range");
        const subject::User& user = m_users.at(index.row());

        switch (static_cast<Field>(index.column()))
        {
        case Field::ID:
            return QVariant::fromValue(static_cast<quint64>(user.id));
        case Field::AGE:
            return QVariant::fromValue(static_cast<quint16>(user.age));  // Каст к 16, т.к. 8 считается символом.
        case Field::EXP:
            return QVariant::fromValue(static_cast<quint16>(user.experience));
        case Field::GENDER:
            return QVariant(user.gender == Gender::FEMALE ? "жен." : "муж.");
        case Field::LAST_NAME:
            return QVariant(user.lastName);
        case Field::FIRST_NAME:
            return QVariant(user.firstName);
        case Field::MID_NAME:
            return QVariant(user.middleName);
        case Field::PHONE:
            return QVariant(user.phoneNumber);
        case Field::CITIZENSHIP:
            return QVariant(user.citizenship);
        default:
            break;
        }
        return QVariant("---");
    }
    return QVariant();
}

QVariant SubjectModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    using namespace subject;
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        return ToString(static_cast<Field>(section));
    }

    return QVariant();
}

void SubjectModel::addRow(const subject::User& rowData)
{
    auto res = std::count_if(
        m_users.begin(), m_users.end(), [id = rowData.id](const subject::User& user) { return id == user.id; });
    if (res > 0)
    {
        QMessageBox::warning(
            nullptr, "Предупреждение", "Такой пользователь уже существует. Пользователь не будет добавлен.");
        return;
    }

    beginInsertRows(QModelIndex(), m_users.size(), m_users.size());
    m_users.push_back(rowData);
    endInsertRows();
}

const std::vector<subject::User>& SubjectModel::GetData() const
{
    return m_users;
}

void SubjectModel::SetData(const std::vector<subject::User>& data)
{
    beginResetModel();
    m_users = data;
    endResetModel();
}
