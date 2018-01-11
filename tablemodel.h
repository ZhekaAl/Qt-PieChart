#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include <QObject>
#include <QPair>
#include <QMutex>


class DataRow
{
public:
    DataRow(QString str,int n);
    QString string;
    double num;
};


class TableModel : public QAbstractTableModel
{
 Q_OBJECT

public:
    TableModel(QObject *parent=0);
    ~TableModel();
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
//    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    Qt::ItemFlags flags (const QModelIndex  &index ) const;
        void deleteRow(int row, QModelIndex index);
public slots:
    void clear();
    void setList(QList<DataRow *> *rows);

private:
    QList<DataRow*> *dataList;
    QMutex m_locker;
};

#endif // TABLEMODEL_H
