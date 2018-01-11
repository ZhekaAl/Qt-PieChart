#include "tablemodel.h"




DataRow::DataRow(QString str,int n):
    string(str),num(n)
{

}


TableModel::TableModel( QObject *parent) : QAbstractTableModel(parent) {
    dataList = NULL;

}

TableModel::~TableModel() {
    if(dataList)
        delete dataList;
}




int TableModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent)

    return dataList ? dataList->size() : 0;
}

Qt::ItemFlags TableModel::flags (const QModelIndex  &index ) const
{
    if (index.row() < 0 || index.row() >= rowCount() || !index.isValid())
    {
        return Qt::NoItemFlags;
    }
    return Qt::ItemIsUserCheckable
            | Qt::ItemIsEnabled
            | Qt::ItemIsSelectable
            | Qt::ItemIsEditable;
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    int row = index.row();
    int column = index.column();

    if(column >= columnCount()
            || row < 0 || row >= rowCount())
        return QVariant();

    if(role == Qt::DisplayRole) {

        DataRow * dataRow = dataList->at(row);

        if (dataList == NULL ) return QVariant();


        if(column==0)
            return dataRow->string;
        if(column==1)
            return dataRow->num;


    }
   return QVariant();
}

int TableModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent)
    return 2;
}

void TableModel::setList(QList<DataRow *> *rows) {
    m_locker.lock();
    if(dataList && dataList->size()) {
        beginRemoveRows(QModelIndex(),0,dataList->size()-1);
        endRemoveRows();
    }
    dataList = rows;

    if(dataList && dataList->size()) {
        beginInsertRows(QModelIndex(),0,dataList->size()-1);
        endInsertRows();
    }

    m_locker.unlock();
}



QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    //    qDebug()<<"role<<orientation<<section"<<role<<orientation<<section;
    if (role == Qt::DisplayRole
            && orientation == Qt::Horizontal
            && section>=0
            && section<2)
    {
        if (section==0)
            return "name";
        if(section==1)
            return "num";
    }

    return QVariant();
}



void TableModel::deleteRow(int row, QModelIndex index) {
    Q_UNUSED(index);

    beginRemoveRows(QModelIndex(),row,row);

    delete dataList->at(row);
    dataList->removeAt(row);

    endRemoveRows();
}



void TableModel::clear() {
    if(dataList){
        if( dataList->size() > 0) {
            beginRemoveRows(QModelIndex(),0,dataList->size()-1);
            for(int i=0; i<dataList->size(); i++)
                delete dataList->at(i);
            dataList->clear();

            endRemoveRows();
        }
    }
}



