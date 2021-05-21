#include <QObject>
#include <QDebug>
#include <QGuiApplication>

class SlideControl : public QObject
{
    Q_OBJECT
    Q_ENUMS(Action)

    Q_PROPERTY(int slide READ getSlide WRITE setSlide NOTIFY slideChanged)
    Q_PROPERTY(QString windowTitle MEMBER mWindowTitle NOTIFY windowTitleChanged)

public:
    enum Slides { LogIn = 0, Dashboard = 1, Settings = 2 };

    SlideControl(QGuiApplication &app);

    void setSlide(const int &slide);
    int getSlide() const;

public slots:
    void updateWindowTitle();
    void onFilePathChanged(const bool &valid);

signals:
    void slideChanged();
    void windowTitleChanged();

private:
    QGuiApplication &mApp;
    Slides mSlide{Slides::Settings};
    QString mWindowTitle;
};
