#include "slidecontrol.h"

SlideControl::SlideControl(QGuiApplication &app) : mApp(app), mSlide(Slides::LogIn) {
    QObject::connect(this, &SlideControl::slideChanged, this, &SlideControl::updateWindowTitle);
}

void SlideControl::setSlide(const int &slide) {
    if (mSlide != slide) {
        mSlide = static_cast<Slides>(slide);
        emit slideChanged();
    }
}

int SlideControl::getSlide() const {
    return static_cast<int>(mSlide);
}

void SlideControl::updateWindowTitle() {
    QString mWindowTitle = "RaspBi";

    switch (mSlide) {
    case Slides::LogIn: mWindowTitle += " > LogIn"; break;
    case Slides::Dashboard: mWindowTitle += " > Dashboard"; break;
    case Slides::Settings: mWindowTitle += " > Settings"; break;
    }

    // making some bullshit to make it work Qt5.13
    // - does not work withouth using setApplicationName
    // - does not work without emitting a signal change
    // - no way it works via QGuiApplication.setApplicationDisplayName
    // - works only if window title is not set on startup
    QCoreApplication::setApplicationName(mWindowTitle);
    emit windowTitleChanged();
    qDebug() << "Window Title:" << mWindowTitle;
}

void SlideControl::onFilePathChanged(const bool &valid) {
    if ( !valid ) {
        setSlide(static_cast<int>(Slides::Settings));
    }
}
