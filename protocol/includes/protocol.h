#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QString>
#include <vector>

namespace Protocol {

/*
 * Defined
 * -------------------------
 * MessageTypes: undefined, values, user, users
 * Representation: dial, number, text, ...
 *
 *
 * Client -> Server
 * -------------------------
 *
 * {
 *  "msg_type": "user",
 *  "user": "name"
 * }
 *
 *
 *
 * Server -> Client
 * --------------------------
 *
 * {
 *  "msg_type": "values",
 *  "values": [
 *      {
 *          "name": "value1",
 *          "value": "0",
 *          "unit": "degree",
 *          "representation": "dial"
 *          "description": "..."
 *      },
 *      ...
 *  ]
 * }
 *
 *
 * {
 *  "msg_type": "users"
 *  "users": [ "user1", "user2", "user3", ... ]
 * }
 *
 */

enum class MessageType {
    Undefined,
    Values,
    User,
    Users
};

enum class DataType {
    Double,
    Bool,
    String
};

enum class Representation {
    Text,
    CircleProgress,
    Led,
    Humidity,
    Pressure,
    Temperature
};

struct Value {
    QString name;
    QString value;
    QString unit;
    DataType datatype;
    Representation representation;
    QString description;

    QJsonObject toJsonObject() {
        QJsonObject json_obj;
        json_obj.insert("name", this->name);
        json_obj.insert("value", this->value);
        json_obj.insert("unit", this->unit);
        json_obj.insert("datatype", static_cast<int>(this->datatype));
        json_obj.insert("representation", static_cast<int>(this->representation));
        json_obj.insert("description", this->description);
        return json_obj;
    }

    QJsonValue toQJsonValue() {
        QJsonValue json_value(this->toJsonObject());
        return json_value;
    }
};

MessageType getTypeOfMessage(const QJsonDocument &json_doc);
std::vector<Value> getValues(const QString &message);
QString getName(const QString &message);
QString getUserName(const QString &message);
QString createUserName(const QString userName);
QString getDataTypeAsString(const DataType dataType);
QString getRepresentationAsString(const Representation representation);

} // namespace Protocol


#endif // PROTOCOL_H
