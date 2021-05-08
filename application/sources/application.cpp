#include "application.h"
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QCommandLineParser>
#include <QQmlContext>
#include <QSettings>
#include <QFile>
#include <QWebSocket>

#include "applicationsettings.h"
#include "programinformation.h"
#include "dataprovider.h"
#include "themeprovider.h"
#include "slidecontrol.h"
#include "valueslist.h"


namespace Gui {

Application::Application()
{
}

Application::~Application()
{
}

int Application::start(int argc, char *argv[])
{
    QCoreApplication::setApplicationName("WebAssembly");
    QCoreApplication::setOrganizationName(ProgramInformation::organization_name);
    QCoreApplication::setApplicationVersion(ProgramInformation::version);

    QApplication app(argc, argv);

    ApplicationSettings applicationSettings;
    applicationSettings.load();

    QWebSocket socket;
    socket.open(QUrl(QString("ws://%1:%2").arg(applicationSettings.getIp(), "1234")));
    DataProvider dataprovider(socket);

    QCommandLineParser parser;
    parser.setApplicationDescription("WebAssembly Application");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.process(app);

    ThemeProvider themeProvider;
    SlideControl slideControl(app);
    ValuesList valuesList;

    QObject::connect(&themeProvider, &ThemeProvider::themeChanged, &applicationSettings, &ApplicationSettings::setThemeName);
    QObject::connect(&dataprovider, &DataProvider::valuesChanged, &valuesList, &ValuesList::onValuesChanged);
    QObject::connect(&applicationSettings, &ApplicationSettings::filePathChanged, &slideControl, &SlideControl::onFilePathChanged);
    QObject::connect(&applicationSettings, &ApplicationSettings::ipChanged, [&](){
        socket.close();
        socket.open(QUrl(QString("ws://%1:%2").arg(applicationSettings.getIp(), "1234")));
        valuesList.clear();
    });

    themeProvider.setCurrentThemeName(applicationSettings.themeName());
    slideControl.updateWindowTitle();

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("dataProvider", &dataprovider);
    engine.rootContext()->setContextProperty("applicationSettings", &applicationSettings);
    engine.rootContext()->setContextProperty("themeProvider", &themeProvider);
    engine.rootContext()->setContextProperty("slideControl", &slideControl);
    engine.rootContext()->setContextProperty("valuesList", &valuesList);
    engine.load(QUrl(QStringLiteral("qrc:/resources/main.qml")));

    return app.exec();
}

} // namespace Gui
