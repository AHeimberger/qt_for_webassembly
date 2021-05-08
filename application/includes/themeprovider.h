#ifndef THEMEPROVIDER_H
#define THEMEPROVIDER_H

#include <QObject>
#include <QColor>
#include <QString>
#include <QMap>
#include <QStringList>

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
    ThemeProvider() {
        DefinedColors *light = new DefinedColors();
        light->flipswitch_background = QColor("gray");
        light->search_background = QColor("#dddddd");
        light->search_text = QColor("#444444");
        light->settings_text = QColor("#000000");
        light->settings_background = QColor("#dddddd");
        light->todo_background = QColor("#dddddd");
        light->todo_tab_background = QColor("#eeeeee");
        light->todo_tab_background_checked = QColor("#dddddd");
        light->todo_text = QColor("#444444");
        light->todo_text_checked = QColor("#444444");
        light->buttonoptions_icontrash_background = QColor("#ff0000");
        light->buttonoptions_icon_background = QColor("#222222");
        light->ruler_background = QColor("#bbbbbb");

        DefinedColors *dark = new DefinedColors();
        dark->flipswitch_background = QColor("green");
        dark->search_background = QColor("#222222");
        dark->search_text = QColor("#ffffff");
        dark->settings_text = QColor("#cccccc");
        dark->settings_background = QColor("#222222");
        dark->todo_background = QColor("#222222");
        dark->todo_tab_background = QColor("#444444");
        dark->todo_tab_background_checked = QColor("#222222");
        dark->todo_text = QColor("#ffffff");
        dark->todo_text_checked = QColor("#ffffff");
        dark->buttonoptions_icontrash_background = QColor("#ff0000");
        dark->buttonoptions_icon_background = QColor("#dddddd");
        dark->ruler_background = QColor("#444444");

        DefinedColors *green = new DefinedColors();
        green->flipswitch_background = QColor("#cccccc");
        green->search_background = QColor("#273C58");
        green->search_text = QColor("#cccccc");
        green->settings_text = QColor("#cccccc");
        green->settings_background = QColor("#54643F");
        green->todo_background = QColor("#912120");
        green->todo_tab_background = QColor("#D3CDC1");
        green->todo_tab_background_checked = QColor("#912120");
        green->todo_text = QColor("#ffffff");
        green->todo_text_checked = QColor("#ffffff");
        green->buttonoptions_icontrash_background = QColor("#C59C5E");
        green->buttonoptions_icon_background = QColor("#dddddd");
        green->ruler_background = QColor("#444444");

        mCurrentThemeName = "Light";
        mThemes["Light"] = light;
        mThemes["Dark"] = dark;
        mThemes["Green"] = green;
    }

    ~ThemeProvider() {
        for (auto theme: mThemes) {
            delete theme;
        }
        mThemes.clear();
    }

    void setCurrentThemeName(const QString &themeName) {
        if ( mThemes.contains(themeName) ) {
            mCurrentThemeName = themeName;
        }
        else {
            mCurrentThemeName = mThemes.firstKey();
        }
    }

    QString currentThemeName() const {
        return mCurrentThemeName;
    }

    QObject *currentTheme() const {
        return mThemes[mCurrentThemeName];
    }

    Q_INVOKABLE void changeTheme() {
        auto iterator = ++(mThemes.find(mCurrentThemeName));
        mCurrentThemeName = (iterator == mThemes.end()) ? mThemes.firstKey() : iterator.key();
        emit themeChanged(mCurrentThemeName);
    }

    QString mCurrentThemeName;
    QMap<QString, DefinedColors*> mThemes;
};

#endif // THEMEPROVIDER_H
