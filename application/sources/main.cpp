#include "application.h"
#include <QMap>
#include <QString>
#include <QDebug>

int main(int argc, char *argv[])
{
	Gui::Application application;
	return application.start(argc, argv);
}

