#ifndef THEMEPROVIDER_H
#define THEMEPROVIDER_H

#include <QObject>
#include <QColor>
#include <QString>
#include <QMap>

class DefinedColors : public QObject {
    Q_OBJECT

    Q_PROPERTY(QColor flipswitch_background MEMBER flipswitch_background CONSTANT)
    Q_PROPERTY(QColor settings_text MEMBER settings_text CONSTANT)
    Q_PROPERTY(QColor settings_background MEMBER settings_background CONSTANT)
    Q_PROPERTY(QColor search_background MEMBER search_background CONSTANT)
    Q_PROPERTY(QColor search_text MEMBER search_text CONSTANT)
    Q_PROPERTY(QColor todo_background MEMBER todo_background CONSTANT)
    Q_PROPERTY(QColor todo_tab_background MEMBER todo_tab_background CONSTANT)
    Q_PROPERTY(QColor todo_tab_background_checked MEMBER todo_tab_background_checked CONSTANT)
    Q_PROPERTY(QColor todo_text MEMBER todo_text CONSTANT)
    Q_PROPERTY(QColor todo_text_checked MEMBER todo_text_checked CONSTANT)
    Q_PROPERTY(QColor buttonoptions_icontrash_background MEMBER buttonoptions_icontrash_background CONSTANT)
    Q_PROPERTY(QColor buttonoptions_icon_background MEMBER buttonoptions_icon_background CONSTANT)
    Q_PROPERTY(QColor ruler_background MEMBER ruler_background CONSTANT)

public:
    QColor flipswitch_background;
    QColor settings_text;
    QColor settings_background;
    QColor search_background;
    QColor search_text;
    QColor todo_background;
    QColor todo_tab_background;
    QColor todo_tab_background_checked;
    QColor todo_text;
    QColor todo_text_checked;
    QColor buttonoptions_icontrash_background;
    QColor buttonoptions_icon_background;
    QColor ruler_background;
};

class ThemeProvider : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString currentThemeName READ currentThemeName NOTIFY themeChanged)
    Q_PROPERTY(QObject* currentTheme READ currentTheme NOTIFY themeChanged)

signals:
    void themeChanged(const QString &themeName);

public:
    ThemeProvider();
    ~ThemeProvider();

    void setCurrentThemeName(const QString &themeName);
    QString currentThemeName() const;
    QObject *currentTheme() const;

    Q_INVOKABLE void changeTheme();

    QString mCurrentThemeName;
    QMap<QString, DefinedColors*> mThemes;
};

#endif // THEMEPROVIDER_H
