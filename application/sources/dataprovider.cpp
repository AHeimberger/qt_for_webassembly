#include "dataprovider.h"

#include <QJsonDocument>
#include <QDebug>

void DataProvider::onConnected() {
    qDebug() << "Connected";
}

void DataProvider::onMessageReceived(const QString &message) {
    QJsonDocument json_doc = QJsonDocument::fromJson(message.toUtf8().data());
    Protocol::MessageType msg_type = Protocol::getTypeOfMessage(json_doc);

    switch (msg_type) {
    case Protocol::MessageType::Values:
        valuesChanged(message);
        break;

    default:
        qDebug() << "-";
    }
}

void DataProvider::onClosed() {
    qDebug() << "Closed";
}

DataProvider::DataProvider(QWebSocket &socket) : m_socket(socket) {
    QObject::connect(&m_socket, &QWebSocket::connected, this, &DataProvider::onConnected);
    QObject::connect(&m_socket, &QWebSocket::textMessageReceived, this, &DataProvider::onMessageReceived);
    QObject::connect(&m_socket, &QWebSocket::disconnected, this, &DataProvider::onClosed);
}

DataProvider::~DataProvider() {
}

void DataProvider::sendMessage(const QString &message) {
    m_socket.sendTextMessage(message);
}
