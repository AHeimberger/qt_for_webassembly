#ifndef APPLICATION_H
#define APPLICATION_H

#include <QNetworkAccessManager>
#include <QNetworkReply>


namespace Gui {

class Application {
public:
    Application();
    ~Application();

    int start(int argc, char *argv[]);
};

} // namespace GUi


#endif // APPLICATION_H
