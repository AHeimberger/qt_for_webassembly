#ifndef SENSOR_DATA_H
#define SENSOR_DATA_H

#include "protocol.h"
#include <QObject>
#include <QTimer>

#ifdef __aarch64__
    #include "SenseHat.h"
#else
class SenseHat {
public:
    float ObtenirPression() { return 0.0; }
    float ObtenirTemperature() { return 0.0; }
    float ObtenirHumidite() { return 0.0; }
    void ObtenirAcceleration(float&, float&, float&) { }
    void ObtenirOrientation(float&, float&, float&) { }
    void ObtenirMagnetisme(float&, float&, float&) { }
    void ViewMessage(const std::string, int=0, uint16_t=0, uint16_t=0) {}
    void Flush() {}
    void LightPixel(int, int, uint16_t) {}
};
#endif

class SensorData : public QObject
{
    Q_OBJECT

    const static int TIME_GET_DATA=250;
    const static int TIME_SHOW_WELCOME=5000;

signals:
    void sendData(const QString &data);

public:
    SensorData();
    void initBoard();
    void updateData();

public slots:
    void showCounterMessage(const int number);
    void showMessage(const QString &message);
    void showWelcomeMessage();

private:
    QTimer m_timer_data;
    QTimer m_timer_welcome;

    SenseHat m_sense_hat;
    Protocol::Value m_pressure;
    Protocol::Value m_temperature;
    Protocol::Value m_humidity;
    Protocol::Value m_acceleration_x;
    Protocol::Value m_acceleration_y;
    Protocol::Value m_acceleration_z;
    Protocol::Value m_orientation_pitch;
    Protocol::Value m_orientation_roll;
    Protocol::Value m_orientation_yaw;
    Protocol::Value m_magnetism_x;
    Protocol::Value m_magnetism_y;
    Protocol::Value m_magnetism_z;

    void messagePrinter(const QString &message);
};

#endif


