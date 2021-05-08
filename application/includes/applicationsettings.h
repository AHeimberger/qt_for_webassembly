#ifndef APPLICATIONSETTINGS_H
#define APPLICATIONSETTINGS_H

#include <QObject>
#include <QSettings>
#include <QString>
#include <QDebug>
#include <QUrl>
#include <QFile>

class ApplicationSettings : public QObject {
    Q_OBJECT

    Q_PROPERTY(bool hasValidFilePath READ hasValidFilePath NOTIFY filePathChanged)
    Q_PROPERTY(QUrl filePath READ getFilePath WRITE setFilePath NOTIFY filePathChanged)
    Q_PROPERTY(double width MEMBER mWidth WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(double height MEMBER mHeight WRITE setHeight NOTIFY heightChanged)
    Q_PROPERTY(double x MEMBER mX WRITE setX NOTIFY xChanged)
    Q_PROPERTY(double y MEMBER mY WRITE setY NOTIFY yChanged)
    Q_PROPERTY(QString themeName READ themeName WRITE setThemeName NOTIFY themeChanged)
    Q_PROPERTY(QString dateTimeFormat MEMBER mDateTimeFormat WRITE setDateTimeFormat NOTIFY dateTimeFormatChanged)
    Q_PROPERTY(QString ip READ getIp WRITE setIp NOTIFY ipChanged)
    Q_PROPERTY(QString userName READ getUserName WRITE setUserName NOTIFY userNameChanged)

signals:
    void filePathChanged(bool valid);
    void widthChanged();
    void heightChanged();
    void xChanged();
    void yChanged();
    void themeChanged();
    void dateTimeFormatChanged();
    void ipChanged();
    void userNameChanged();

public:
    ApplicationSettings() :
        mSettings("HomeHiller", "QtWasm") {
    }

    void load() {
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

    bool hasValidFilePath() {
        return QFile::exists(mFilePath.toLocalFile());
    }

    QUrl getFilePath() {
        return mFilePath;
    }

    void setFilePath(const QUrl &filePath) {
        if (filePath != mFilePath)
        {
            mFilePath = filePath;
            mSettings.setValue("storage/filepath", mFilePath);
            emit filePathChanged(hasValidFilePath());
        }
    }

    void setWidth(const double &width) {
        mWidth = width;
    }

    void setHeight(const double &height) {
        mHeight = height;
    }

    void setX(const double &x) {
        mX = x;
    }

    void setY(const double &y) {
        mY = y;
    }

    void setThemeName(const QString &themeName) {
        mThemeName = themeName;
        emit themeChanged();
    }

    const QString &themeName() {
        return mThemeName;
    }

    void setDateTimeFormat(const QString &dateTimeFormat) {
        if (dateTimeFormat == mDateTimeFormat)
            return;

        mDateTimeFormat = dateTimeFormat;
        emit dateTimeFormatChanged();
    }

    QString getIp() {
        return mIp;
    }

    void setIp(const QString &ip) {
        if (ip == mIp)
            return;

        mIp = ip;
        emit ipChanged();
    }

    QString getUserName() {
        return mUserName;
    }

    void setUserName(const QString &userName) {
        if (userName == mUserName)
            return;

        mUserName = userName;
        emit userNameChanged();
    }

    Q_INVOKABLE void saveApplicationSettings() {
        mSettings.setValue("window/width", mWidth);
        mSettings.setValue("window/height", mHeight);
        mSettings.setValue("window/x", mX);
        mSettings.setValue("window/y", mY);
        mSettings.setValue("user/themename", mThemeName);
        mSettings.setValue("user/datetimeformat", mDateTimeFormat);
        mSettings.setValue("network/ip", mIp);
        printSettings();
    }

protected:
    void printSettings() {
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

private:
    QSettings mSettings;
    QUrl mFilePath;
    double mWidth;
    double mHeight;
    double mX;
    double mY;
    QString mThemeName;
    QString mDateTimeFormat;
    QString mIp;
    QString mUserName;
};

#endif // APPLICATIONSETTINGS_H
