#include <QCoreApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include "server.h"
#include "sensor_data.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription("QWebSocket Server");
    parser.addHelpOption();

    QCommandLineOption portOption(QStringList() << "p" << "port",
            QCoreApplication::translate("main", "Port for echoserver [default: 1234]."),
            QCoreApplication::translate("main", "port"), QLatin1String("1234"));
    parser.addOption(portOption);
    parser.process(app);
    int port = parser.value(portOption).toInt();

    Server server(port);
    SensorData sensorData;
    sensorData.initBoard();

    QObject::connect(&server, &Server::closed, &app, &QCoreApplication::quit);
    QObject::connect(&server, &Server::numberClientsChanged, &sensorData, &SensorData::showCounterMessage);
    QObject::connect(&server, &Server::receivedData, &sensorData, &SensorData::showMessage);
    QObject::connect(&sensorData, &SensorData::sendData, &server, &Server::sendData);

    return app.exec();
}
