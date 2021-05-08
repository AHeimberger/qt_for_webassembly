#include "sensor_data.h"
#include <QDateTime>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>

#ifdef __aarch64__
    #include <wiringPi.h>
    #include <wiringPiI2C.h>
    #include <stdlib.h>
#else
    int wiringPiI2CSetup(int) { return -1; }
    uint8_t wiringPiI2CReadReg8(int, int) { return -1; }
#endif

SensorData::SensorData() :
    m_timer(),
    m_fd(),
    m_receive_buffer(),
    m_initialized(false)
{
    QObject::connect(&m_timer, &QTimer::timeout, this, &SensorData::updateData);
    m_timer.start(TIME_GET_DATA);

    using namespace Protocol;
    m_temperature_overrange = { "temperature_overrange", "", "none", DataType::Double, Representation::Text, "Off-chip temperature sensor overrange!" };
    m_temperature_failure = { "temperature_failure", "", "none", DataType::Double, Representation::Text, "No external temperature sensor!" };
    m_temperature_celsius = { "temperature_celsius", "°C", "none", DataType::Double, Representation::Text, "Current external Sensor Temperature" };
    m_brightness_overrange = { "brightness_overrange", "", "none", DataType::Double, Representation::Text, "Onboard brightness sensor overrange!" };
    m_brightness_failure = { "brightness_failure", "", "none", DataType::Double, Representation::Text, "Onboard brightness sensor failure!" };
    m_brightness_lux = { "brightness_lux", "", "none", DataType::Double, Representation::Text, "Current onboard sensor brightness" };
    m_celsius = { "celsius", "°C", "none", DataType::Double, Representation::Text, "Current onboard sensor temperature" };
    m_humidity = { "humidity", "", "none", DataType::Double, Representation::Text, "Current onboard sensor humidity" };
    m_validity = { "validity", "", "none", DataType::Double, Representation::Text, "Temperature and humidity sensor data may not be up to date" };
    m_baro_celsius = { "baro_celsius", "°C", "none", DataType::Double, Representation::Text, "Current barometer temperature" };
    m_baro_pascal = { "baro_pascal", "", "none", DataType::Double, Representation::Text, "Current barometer pressure" };
    m_baro_validity = { "baro_validity", "", "none", DataType::Double, Representation::Text, "Onboard barometer works abnormally" };
    m_body_detected = { "body_detected", "", "none", DataType::Double, Representation::Text, "Body detection" };
}

void SensorData::initBoard() {
#ifdef __aarch64__
    qDebug() << "Board Architecture: ARM 64Bit";
#else
    qDebug() << "Board Architecture: Other";
#endif

    m_fd = wiringPiI2CSetup(0x17);
    m_initialized = (m_fd != -1);
    if ( !m_initialized) {
        return;
    }

    m_timer.setInterval(TIME_GET_DATA);
    qDebug() << QDateTime::currentDateTime().toString("hh:mm:ss.zzz") << "Board initialized update data after" << TIME_GET_DATA << "msec";
}

void SensorData::updateData() {
    if ( !m_initialized ) {
        qDebug() << QDateTime::currentDateTime().toString("hh:mm:ss.zzz") << "Board not initialized retrying after" << TIME_RETRY_CONNECT << "msec";
        initBoard();
        m_timer.setInterval(TIME_RETRY_CONNECT);
        return;
    }

    for (int i = TEMP_REG; i <= HUMAN_DETECT; i++) {
        m_receive_buffer[i] = wiringPiI2CReadReg8(m_fd, i);
    }

    m_temperature_overrange.value = QString("%1").arg(static_cast<bool>(m_receive_buffer[STATUS_REG] & 0x01));
    m_temperature_failure.value = QString("%1").arg(static_cast<bool>(m_receive_buffer[STATUS_REG] & 0x02));
    m_temperature_celsius.value = QString("%1").arg(static_cast<int>(m_receive_buffer[TEMP_REG]));
    m_brightness_overrange.value = QString("%1").arg(static_cast<bool>(m_receive_buffer[STATUS_REG] & 0x04));
    m_brightness_failure.value = QString("%1").arg(static_cast<bool>(m_receive_buffer[STATUS_REG] & 0x08));
    m_brightness_lux.value = QString("%1").arg(static_cast<int>(m_receive_buffer[LIGHT_REG_H] << 8) | (m_receive_buffer[LIGHT_REG_L]));
    m_celsius.value = QString("%1").arg(static_cast<int>(m_receive_buffer[ON_BOARD_TEMP_REG]));
    m_humidity.value = QString("%1").arg(static_cast<int>(m_receive_buffer[ON_BOARD_HUMIDITY_REG]));
    m_validity.value = QString("%1").arg(static_cast<bool>(m_receive_buffer[ON_BOARD_SENSOR_ERROR] != 0));
    m_baro_celsius.value = QString("%1").arg(static_cast<int>(m_receive_buffer[BMP280_TEMP_REG]));
    m_baro_pascal.value = QString("%1").arg(static_cast<int>(m_receive_buffer[BMP280_PRESSURE_REG_L]) | static_cast<int>(m_receive_buffer[BMP280_PRESSURE_REG_M]) << 8 | static_cast<int>(m_receive_buffer[BMP280_PRESSURE_REG_H]) << 16);
    m_baro_validity.value = QString("%1").arg(static_cast<bool>(m_receive_buffer[BMP280_STATUS] == 0));
    m_body_detected.value = QString("%1").arg(static_cast<bool>(m_receive_buffer[HUMAN_DETECT] == 1));

    QJsonArray json_array;
    json_array.append(m_temperature_overrange.toJsonObject());
    json_array.append(m_temperature_failure.toJsonObject());
    json_array.append(m_temperature_celsius.toJsonObject());
    json_array.append(m_brightness_overrange.toJsonObject());
    json_array.append(m_brightness_failure.toJsonObject());
    json_array.append(m_brightness_lux.toJsonObject());
    json_array.append(m_celsius.toJsonObject());
    json_array.append(m_humidity.toJsonObject());
    json_array.append(m_validity.toJsonObject());
    json_array.append(m_baro_celsius.toJsonObject());
    json_array.append(m_baro_pascal.toJsonObject());
    json_array.append(m_baro_validity.toJsonObject());
    json_array.append(m_body_detected.toJsonObject());

    QJsonObject json_obj;
    json_obj.insert("msg_type", "values");
    json_obj.insert("values", json_array);
    QJsonDocument json_doc(json_obj);
    emit sendData(json_doc.toJson());
}
