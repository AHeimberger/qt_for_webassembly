#ifndef DATAPROVIDER_H
#define DATAPROVIDER_H

#include "protocol.h"
#include <QWebSocket>
#include <QObject>

class DataProvider : public QObject {
    Q_OBJECT

signals:
    void valuesChanged(const QString &message);

public slots:
    void onConnected();
    void onMessageReceived(const QString &message);
    void onClosed();

public:
    DataProvider(QWebSocket &socket);

    virtual ~DataProvider();

    Q_INVOKABLE void sendMessage(const QString &message);

private:
    QWebSocket &m_socket;
};

#endif // DATAPROVIDER_H
