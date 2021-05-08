#include "sensor_data.h"
#include <QDateTime>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>
#include <QFuture>
#include <QtConcurrent>

SensorData::SensorData() :
    m_timer_data()
{
    QObject::connect(&m_timer_data, &QTimer::timeout, this, &SensorData::updateData);
    m_timer_data.start(TIME_GET_DATA);
    QObject::connect(&m_timer_welcome, &QTimer::timeout, this, &SensorData::showWelcomeMessage);
    m_timer_welcome.start(TIME_SHOW_WELCOME);


    using namespace Protocol;
    m_pressure = { "pressure", "", "hPa", DataType::Double, Representation::Text, "" };
    m_temperature = { "temperature", "", "°C", DataType::Double, Representation::Text, "" };
    m_humidity = { "humidity", "", "%", DataType::Double, Representation::Text, "" };
    m_acceleration_x = { "acceleration_x", "", "g", DataType::Double, Representation::Text, "" };
    m_acceleration_y = { "acceleration_y", "", "g", DataType::Double, Representation::Text, "" };
    m_acceleration_z = { "acceleration_z", "", "g", DataType::Double, Representation::Text, "" };
    m_orientation_pitch = { "orientation_pitch", "", "", DataType::Double, Representation::Text, "" };
    m_orientation_roll = { "orientation_roll", "", "", DataType::Double, Representation::Text, "" };
    m_orientation_yaw = { "orientation_yaw", "", "", DataType::Double, Representation::Text, "" };
    m_magnetism_x = { "magnetism_x", "", "µT", DataType::Double, Representation::Text, "" };
    m_magnetism_y = { "magnetism_y", "", "µT", DataType::Double, Representation::Text, "" };
    m_magnetism_z = { "magnetism_z", "", "µT", DataType::Double, Representation::Text, "" };
}

void SensorData::initBoard() {
#ifdef __aarch64__
    qDebug() << "Board Architecture: ARM 64Bit";
#else
    qDebug() << "Board Architecture: Other";
#endif

    m_timer_data.setInterval(TIME_GET_DATA);
    qDebug() << QDateTime::currentDateTime().toString("hh:mm:ss.zzz") << "Board initialized update data after" << TIME_GET_DATA << "msec";
    showWelcomeMessage();
}

void SensorData::updateData() {
    float xa, ya, za;
    float xm, ym, zm;
    float pitch, roll, yaw;
    m_sense_hat.ObtenirAcceleration(xa, ya, za);
    m_sense_hat.ObtenirOrientation(pitch, roll, yaw);
    m_sense_hat.ObtenirMagnetisme(xm, ym, zm);

    m_pressure.value = QString("%1").arg(m_sense_hat.ObtenirPression());
    m_temperature.value = QString("%1").arg(m_sense_hat.ObtenirTemperature());
    m_humidity.value = QString("%1").arg(m_sense_hat.ObtenirHumidite());
    m_acceleration_x.value = QString("%1").arg(xa);
    m_acceleration_y.value = QString("%1").arg(ya);
    m_acceleration_z.value = QString("%1").arg(za);
    m_orientation_pitch.value = QString("%1").arg(pitch);
    m_orientation_roll.value = QString("%1").arg(roll);
    m_orientation_yaw.value = QString("%1").arg(yaw);
    m_magnetism_x.value = QString("%1").arg(xm);
    m_magnetism_y.value = QString("%1").arg(ym);
    m_magnetism_z.value = QString("%1").arg(zm);

    QJsonArray json_array;
    json_array.append(m_pressure.toJsonObject());
    json_array.append(m_temperature.toJsonObject());
    json_array.append(m_humidity.toJsonObject());
    json_array.append(m_acceleration_x.toJsonObject());
    json_array.append(m_acceleration_y.toJsonObject());
    json_array.append(m_acceleration_z.toJsonObject());
    json_array.append(m_orientation_pitch.toJsonObject());
    json_array.append(m_orientation_roll.toJsonObject());
    json_array.append(m_orientation_yaw.toJsonObject());
    json_array.append(m_magnetism_x.toJsonObject());
    json_array.append(m_magnetism_y.toJsonObject());
    json_array.append(m_magnetism_z.toJsonObject());

    QJsonObject json_obj;
    json_obj.insert("msg_type", "values");
    json_obj.insert("values", json_array);
    QJsonDocument json_doc(json_obj);
    emit sendData(json_doc.toJson());
}

void SensorData::showCounterMessage(const int number) {
    m_sense_hat.Flush();

    if (number <= 0) {
        showWelcomeMessage();
        m_timer_welcome.start(TIME_SHOW_WELCOME);
        return;
    }

    m_timer_welcome.stop();
    for (int i = 0; i < number; i++) {
        m_sense_hat.LightPixel(i/8, i%8, 31);
    }
}

void SensorData::showWelcomeMessage() {
    showMessage("ecc21");
}

void SensorData::showMessage(const QString &message) {
    QFuture<void> future = QtConcurrent::run(this, &SensorData::messagePrinter, message);
}

void SensorData::messagePrinter(const QString &message) {
    std::string str;
    str += message.toUtf8().data();
    str += "  ";
    m_sense_hat.ViewMessage(str);
}
