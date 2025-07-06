#ifndef SUBJECTMODEL_H
#define SUBJECTMODEL_H

#include <QAbstractTableModel>
#include <QObject>

class SubjectModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit SubjectModel(QObject *parent = nullptr);
};

#endif // SUBJECTMODEL_H
