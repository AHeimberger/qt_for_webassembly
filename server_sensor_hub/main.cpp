#include <QCoreApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include "server.h"
#include "sensor_data.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription("QWebSocket Server");
    parser.addHelpOption();

    QCommandLineOption portOption(QStringList() << "p" << "port",
            QCoreApplication::translate("main", "Port for echoserver [default: 1234]."),
            QCoreApplication::translate("main", "port"), QLatin1String("1234"));
    parser.addOption(portOption);
    parser.process(a);
    int port = parser.value(portOption).toInt();

    Server server(port);
    SensorData sensorData;
    sensorData.initBoard();

    QObject::connect(&server, &Server::closed, &a, &QCoreApplication::quit);
    QObject::connect(&sensorData, &SensorData::sendData, &server, &Server::sendData);

    return a.exec();
}
