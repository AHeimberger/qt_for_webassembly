#ifndef VALUESLIST_H
#define VALUESLIST_H

#include "protocol.h"
#include <vector>
#include <QString>
#include <QAbstractListModel>

class ValuesList : public QAbstractListModel {
    Q_OBJECT

public slots:
    void onValuesChanged(const QString &message);

public:
    enum Roles {
      Name = Qt::UserRole + 1,
      CurrentValue,
      Unit,
      DataType,
      Representation,
      Description
    };

    ValuesList();

    // abstract list model interface
    virtual QVariant data(const QModelIndex &index, int role) const override final;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role) override final;
    virtual int rowCount( const QModelIndex &parent = QModelIndex()) const override final;
    virtual QHash<int, QByteArray> roleNames() const override final;
    void clear();

private:
    std::vector<Protocol::Value> m_values;
};

#endif // VALUELIST_H
