#ifndef APPLICATIONSETTINGS_H
#define APPLICATIONSETTINGS_H

#include <QObject>
#include <QSettings>
#include <QString>
#include <QUrl>

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
    ApplicationSettings();

    void load();
    bool hasValidFilePath();
    QUrl getFilePath();
    void setFilePath(const QUrl &filePath);
    void setWidth(const double &width);
    void setHeight(const double &height);
    void setX(const double &x);
    void setY(const double &y);
    void setThemeName(const QString &themeName);
    const QString &themeName();
    void setDateTimeFormat(const QString &dateTimeFormat);
    QString getIp();
    void setIp(const QString &ip);
    QString getUserName();
    void setUserName(const QString &userName);

    Q_INVOKABLE void saveApplicationSettings();

protected:
    void printSettings();

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
