#include "valueslist.h"



void ValuesList::onValuesChanged(const QString &message) {
    if (m_values.empty()) {
        beginResetModel();
        m_values = Protocol::getValues(message);
        endResetModel();
        return;
    }

    m_values = Protocol::getValues(message);
    emit dataChanged(this->index(0, 0), this->index(m_values.size()-1, 0));
}

ValuesList::ValuesList() {}

QVariant ValuesList::data(const QModelIndex &index, int role) const {
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

bool ValuesList::setData(const QModelIndex &index, const QVariant &value, int role) {
    Q_UNUSED(index)
    Q_UNUSED(value)
    Q_UNUSED(role)
    return true;
}

int ValuesList::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent)
    return m_values.size();
}

QHash<int, QByteArray> ValuesList::roleNames() const {
    auto roles = QAbstractListModel::roleNames();
    roles.insert(Name, "name");
    roles.insert(CurrentValue, "currentValue");
    roles.insert(Unit, "unit");
    roles.insert(DataType, "dataType");
    roles.insert(Representation, "representation");
    roles.insert(Description, "description");
    return roles;
}

void ValuesList::clear() {
    beginResetModel();
    m_values.clear();
    endResetModel();
}
