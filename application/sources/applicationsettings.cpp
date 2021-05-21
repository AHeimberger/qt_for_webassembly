#include "applicationsettings.h"
#include <QDebug>
#include <QFile>

ApplicationSettings::ApplicationSettings() :
    mSettings("HomeHiller", "QtWasm") {
}

void ApplicationSettings::load() {
    double screenWidth = 2560;
    double screenHeight = 1080;
    mFilePath = mSettings.value("storage/filepath", "").toString();
    mWidth = mSettings.value("window/width", 350).toDouble();
    mHeight = mSettings.value("window/height", 430).toDouble();
    mX = mSettings.value("window/x", screenWidth/2-350/2).toDouble();
    mY = mSettings.value("window/y", screenHeight/2-430/2).toDouble();
    mThemeName = mSettings.value("user/themename", "Light").toString();
    mDateTimeFormat = mSettings.value("user/datetimeformat", "dd/mm/yyyy").toString();
    mIp = mSettings.value("network/ip", "192.168.178.39").toString();
    printSettings();
}

bool ApplicationSettings::hasValidFilePath() {
    return QFile::exists(mFilePath.toLocalFile());
}

QUrl ApplicationSettings::getFilePath() {
    return mFilePath;
}

void ApplicationSettings::setFilePath(const QUrl &filePath) {
    if (filePath != mFilePath)
    {
        mFilePath = filePath;
        mSettings.setValue("storage/filepath", mFilePath);
        emit filePathChanged(hasValidFilePath());
    }
}

void ApplicationSettings::setWidth(const double &width) {
    mWidth = width;
}

void ApplicationSettings::setHeight(const double &height) {
    mHeight = height;
}

void ApplicationSettings::setX(const double &x) {
    mX = x;
}

void ApplicationSettings::setY(const double &y) {
    mY = y;
}

void ApplicationSettings::setThemeName(const QString &themeName) {
    mThemeName = themeName;
    emit themeChanged();
}

const QString &ApplicationSettings::themeName() {
    return mThemeName;
}

void ApplicationSettings::setDateTimeFormat(const QString &dateTimeFormat) {
    if (dateTimeFormat == mDateTimeFormat)
        return;

    mDateTimeFormat = dateTimeFormat;
    emit dateTimeFormatChanged();
}

QString ApplicationSettings::getIp() {
    return mIp;
}

void ApplicationSettings::setIp(const QString &ip) {
    if (ip == mIp)
        return;

    mIp = ip;
    emit ipChanged();
}

QString ApplicationSettings::getUserName() {
    return mUserName;
}

void ApplicationSettings::setUserName(const QString &userName) {
    if (userName == mUserName)
        return;

    mUserName = userName;
    emit userNameChanged();
}

void ApplicationSettings::saveApplicationSettings() {
    mSettings.setValue("window/width", mWidth);
    mSettings.setValue("window/height", mHeight);
    mSettings.setValue("window/x", mX);
    mSettings.setValue("window/y", mY);
    mSettings.setValue("user/themename", mThemeName);
    mSettings.setValue("user/datetimeformat", mDateTimeFormat);
    mSettings.setValue("network/ip", mIp);
    printSettings();
}

void ApplicationSettings::printSettings() {
    qDebug().noquote().nospace() << "Application Settings: " <<
                                    "\n - filePath: " << mFilePath <<
                                    "\n - width: " << mWidth <<
                                    "\n - height: " << mHeight <<
                                    "\n - x: " << mX <<
                                    "\n - y: " << mY <<
                                    "\n - darkMode: " << mThemeName <<
                                    "\n - dateTimeFormat:" << mDateTimeFormat <<
                                    "\n - ip: " << mIp;
}
