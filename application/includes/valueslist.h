#ifndef VALUESLIST_H
#define VALUESLIST_H

#include "protocol.h"
#include <vector>
#include <QString>
#include <QAbstractListModel>

class ValuesList : public QAbstractListModel {
    Q_OBJECT

public slots:
    void onValuesChanged(const QString &message) {
        if (m_values.empty()) {
            beginResetModel();
            m_values = Protocol::getValues(message);
            endResetModel();
            return;
        }

        m_values = Protocol::getValues(message);
        emit dataChanged(this->index(0, 0), this->index(m_values.size()-1, 0));
    }

public:
    enum Roles {
      Name = Qt::UserRole + 1,
      CurrentValue,
      Unit,
      DataType,
      Representation,
      Description
    };

    ValuesList() {}

    // abstract list model interface
    virtual QVariant data(const QModelIndex &index, int role) const override final {
        if (static_cast<size_t>(index.row()) >= m_values.size())
            return QVariant();

        Protocol::Value value = m_values.at(index.row());

        switch (role) {
        case Name: return value.name;
        case CurrentValue: {
            switch(value.datatype) {
                case Protocol::DataType::Double: return value.value.toDouble();
                case Protocol::DataType::Bool: return QVariant(value.value).toBool();
                default: return value.value;
            }
        }
        case Unit: return value.unit;
        case DataType: return Protocol::getDataTypeAsString(value.datatype);
        case Representation: return Protocol::getRepresentationAsString(value.representation);
        case Description: return value.description;
        default:
            return QVariant();
        }
    }

    virtual bool setData(const QModelIndex &index, const QVariant &value, int role) override final {
        Q_UNUSED(index)
        Q_UNUSED(value)
        Q_UNUSED(role)
        return true;
    }

    virtual int rowCount( const QModelIndex &parent = QModelIndex()) const override final {
        Q_UNUSED(parent)
        return m_values.size();
    }

    virtual QHash<int, QByteArray> roleNames() const override final {
        auto roles = QAbstractListModel::roleNames();
        roles.insert(Name, "name");
        roles.insert(CurrentValue, "currentValue");
        roles.insert(Unit, "unit");
        roles.insert(DataType, "dataType");
        roles.insert(Representation, "representation");
        roles.insert(Description, "description");
        return roles;
    }

    void clear() {
        beginResetModel();
        m_values.clear();
        endResetModel();
    }

private:
    std::vector<Protocol::Value> m_values;
};

#endif // VALUELIST_H
