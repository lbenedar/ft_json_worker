#include "trafficitemmodel.h"
#include <QLinkedList>
#include <QItemSelectionModel>
#include <QMutableLinkedListIterator>

TrafficItemModel::TrafficItemModel(QObject *parent): QAbstractItemModel(parent)
{
    listJson = new QLinkedList<SocialTraffic>();\
}

QModelIndex TrafficItemModel::index(int row, int column, const QModelIndex &parent) const
{
    if (row >=0 && column >= 0)
        return createIndex(row, column);
    return QModelIndex();
}

QModelIndex TrafficItemModel::parent(const QModelIndex &index) const
{
    return (QModelIndex());
}

int TrafficItemModel::rowCount(const QModelIndex &parent) const
{
    return listJson->count();
}

int TrafficItemModel::columnCount(const QModelIndex &parent) const
{
    return (5);
}

SocialTraffic* TrafficItemModel::getElemByIndex(int index) const
{
    if (!listJson->count())
        return 0;
    QMutableLinkedListIterator<SocialTraffic> i(*listJson);
    int currIndex = 0;
    while(i.hasNext())
    {
        if (index == currIndex)
            return (&i.next());
        i.next();
        currIndex++;
    }
    return (0);
}

QLinkedList<SocialTraffic>* TrafficItemModel::getList() const
{
    return listJson;
}

bool TrafficItemModel::clearModel()
{
    beginRemoveRows(QModelIndex(), 0, listJson->count() - 1);
    listJson->clear();
    endRemoveRows();
}

QVariant TrafficItemModel::data(const QModelIndex &index, int role) const
{
    if ((!index.isValid()) || (role != Qt::DisplayRole))
        return QVariant();
    int row_index = index.row();
    int column_index = index.column();
    const SocialTraffic* currentPerson = getElemByIndex(row_index);

    switch (column_index)
    {
        case 0:
            return QString::number(currentPerson->iD);
        case 1:
            return QString::number(currentPerson->siteID);
        case 2:
            return currentPerson->link;
        case 3:
            return currentPerson->site;
        case 4:
            return currentPerson->share;
    }
    return QVariant();
}

void TrafficItemModel::insert(SocialTraffic jsonElem)
{
    int last_index = listJson->count();
    beginInsertRows(QModelIndex(), last_index, last_index);
    listJson->append(jsonElem);
    endInsertRows();
}

void TrafficItemModel::remove(int index)
{
    beginRemoveRows(QModelIndex(), index, index);
    const SocialTraffic* currentPerson = getElemByIndex(index);
    if (currentPerson)
        listJson->removeOne(*currentPerson);
    endRemoveRows();
}

void TrafficItemModel::change(int index, SocialTraffic jsonElem)
{
    QMutableLinkedListIterator<SocialTraffic> i(*listJson);
    int currIndex = 0;
    while(i.hasNext())
    {
        i.next();
        if (index == currIndex)
        {
            i.setValue(jsonElem);
            emit dataChanged(this->index(index, 0), this->index(index,4));
            break ;
        }
        currIndex++;
    }
}

QVariant TrafficItemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if ((role == Qt::DisplayRole) && (orientation == Qt::Horizontal))
    {
        switch (section)
        {
            case 0:
                return QVariant("ID");
            case 1:
                return QVariant("Site ID");
            case 2:
                return QVariant("Link");
            case 3:
                return QVariant("Site");
            case 4:
                return QVariant("Share");
            default:
                return QVariant();
        }
    }
    return QVariant();
}


