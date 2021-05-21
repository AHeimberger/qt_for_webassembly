#include "themeprovider.h"

ThemeProvider::ThemeProvider() {
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

ThemeProvider::~ThemeProvider() {
    for (auto theme: mThemes) {
        delete theme;
    }
    mThemes.clear();
}

void ThemeProvider::setCurrentThemeName(const QString &themeName) {
    if ( mThemes.contains(themeName) ) {
        mCurrentThemeName = themeName;
    }
    else {
        mCurrentThemeName = mThemes.firstKey();
    }
}

QString ThemeProvider::currentThemeName() const {
    return mCurrentThemeName;
}

QObject *ThemeProvider::currentTheme() const {
    return mThemes[mCurrentThemeName];
}

void ThemeProvider::changeTheme() {
    auto iterator = ++(mThemes.find(mCurrentThemeName));
    mCurrentThemeName = (iterator == mThemes.end()) ? mThemes.firstKey() : iterator.key();
    emit themeChanged(mCurrentThemeName);
}
