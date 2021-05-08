#include "protocol.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

namespace Protocol {

MessageType getTypeOfMessage(const QJsonDocument &json_doc) {
    QJsonObject json_obj = json_doc.object();
    QString msg_type = json_obj["msg_type"].toString();
    if (msg_type == "values") return MessageType::Values;
    if (msg_type == "user") return MessageType::User;
    if (msg_type == "users") return MessageType::Users;
    return MessageType::Undefined;
}

std::vector<Value> getValues(const QString &message) {
    QJsonDocument json_doc = QJsonDocument::fromJson(message.toUtf8().data());
    QJsonObject json_obj = json_doc.object();
    QJsonArray json_ar = json_obj["values"].toArray();

    std::vector<Value> values;
    std::for_each(json_ar.begin(), json_ar.end(), [&](QJsonValue value){
        Value new_value{
            value.toObject().value("name").toString(),
                    value.toObject().value("value").toString(),
                    value.toObject().value("unit").toString(),
                    static_cast<DataType>(value.toObject().value("datatype").toInt()),
                    static_cast<Representation>(value.toObject().value("representation").toInt()),
                    value.toObject()["description"].toString()
        };
        values.push_back(new_value);
    });
    return values;
}

QString getName(const QString &message) {
    QJsonDocument json_doc = QJsonDocument::fromJson(message.toUtf8().data());
    QJsonObject json_obj = json_doc.object();
    return json_obj["Username"].toString();
}

QString getUserName(const QString &message) {
    QJsonDocument json_doc = QJsonDocument::fromJson(message.toUtf8().data());
    QJsonObject json_obj = json_doc.object();
    return json_obj["Username"].toString();
}

QString createUserName(const QString userName) {
    QJsonObject json_obj;
    json_obj.insert("Username", userName);
    QJsonDocument json_doc(json_obj);
    return json_doc.toJson();
}

QString getDataTypeAsString(const DataType dataType) {
    switch(dataType) {
    case DataType::Bool: return "bool";
    case DataType::Double: return "double";
    case DataType::String: return "string";
    }

    return "";
}

QString getRepresentationAsString(const Representation representation) {
    switch(representation) {
    case Representation::Text: return "text";
    case Representation::CircleProgress: return "circleprogress";
    case Representation::Led: return "led";
    case Representation::Humidity: return "humidity";
    case Representation::Pressure: return "pressure";
    case Representation::Temperature: return "temperature";
    }

    return "";
}

} // namespace Protocol
