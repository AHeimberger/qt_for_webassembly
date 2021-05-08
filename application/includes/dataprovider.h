#ifndef DATAPROVIDER_H
#define DATAPROVIDER_H

#include "protocol.h"
#include <QJsonDocument>
#include <QWebSocket>
#include <QObject>
#include <QDebug>
#include <list>

class DataProvider : public QObject {
    Q_OBJECT

signals:
    void valuesChanged(const QString &message);

public slots:
    void onConnected() {
        qDebug() << "Connected";
    }

    void onMessageReceived(const QString &message) {
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

    void onClosed() {
        qDebug() << "Closed";
    }

public:
    DataProvider(QWebSocket &socket) : m_socket(socket) {
        QObject::connect(&m_socket, &QWebSocket::connected, this, &DataProvider::onConnected);
        QObject::connect(&m_socket, &QWebSocket::textMessageReceived, this, &DataProvider::onMessageReceived);
        QObject::connect(&m_socket, &QWebSocket::disconnected, this, &DataProvider::onClosed);
    }

    virtual ~DataProvider() {
    }

    Q_INVOKABLE void sendMessage(const QString &message) {
        m_socket.sendTextMessage(message);
    }

private:
    QWebSocket &m_socket;
};

#endif // DATAPROVIDER_H
