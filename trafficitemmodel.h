#ifndef TRAFFICITEMMODEL_H
#define TRAFFICITEMMODEL_H

#include <QAbstractItemModel>
#include <QLinkedList>
#include <QItemSelectionModel>
#include <socialtraffic.h>


class TrafficItemModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit TrafficItemModel(QObject *parent = nullptr);

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    void insert(SocialTraffic jsonElem);
    void remove(int index);
    void change(int index, SocialTraffic jsonElem);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    QLinkedList<SocialTraffic>* getList() const;
    bool clearModel();

private:

    QLinkedList<SocialTraffic> *listJson;
    QVariant data(const QModelIndex &index, int role) const override;
    SocialTraffic *getElemByIndex(int index) const;
};

#endif // TRAFFICITEMMODEL_H
