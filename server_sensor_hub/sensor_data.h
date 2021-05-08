#ifndef SENSOR_DATA_H
#define SENSOR_DATA_H

#include "protocol.h"
#include <QObject>
#include <QTimer>

class SensorData : public QObject
{
    Q_OBJECT

    const static int TIME_RETRY_CONNECT=2000;
    const static int TIME_GET_DATA=100;

    const static uint8_t TEMP_REG=0x01;
    const static uint8_t LIGHT_REG_L=0x02;
    const static uint8_t LIGHT_REG_H=0x03;
    const static uint8_t STATUS_REG=0x04;
    const static uint8_t ON_BOARD_TEMP_REG=0x05;
    const static uint8_t ON_BOARD_HUMIDITY_REG=0x06;
    const static uint8_t ON_BOARD_SENSOR_ERROR=0x07;
    const static uint8_t BMP280_TEMP_REG=0x08;
    const static uint8_t BMP280_PRESSURE_REG_L=0x09;
    const static uint8_t BMP280_PRESSURE_REG_M=0x0A;
    const static uint8_t BMP280_PRESSURE_REG_H=0x0B;
    const static uint8_t BMP280_STATUS=0x0C;
    const static uint8_t HUMAN_DETECT=0x0D;

public:
    SensorData();
    void initBoard();
    void updateData();

signals:
    void sendData(const QString &data);

private:
    QTimer m_timer;

    int m_fd;
    uint8_t m_receive_buffer[HUMAN_DETECT + 1];
    bool m_initialized;

    Protocol::Value m_temperature_overrange;
    Protocol::Value m_temperature_failure;
    Protocol::Value m_temperature_celsius;
    Protocol::Value m_brightness_overrange;
    Protocol::Value m_brightness_failure;
    Protocol::Value m_brightness_lux;
    Protocol::Value m_celsius;
    Protocol::Value m_humidity;
    Protocol::Value m_validity;
    Protocol::Value m_baro_celsius;
    Protocol::Value m_baro_pascal;
    Protocol::Value m_baro_validity;
    Protocol::Value m_body_detected;
};

#endif


