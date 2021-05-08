import QtQuick 2.9
import QtQuick.Controls 2.1
import Qt.labs.platform 1.0
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3

ApplicationWindow {
    title: slideControl.windowTitle
    width: applicationSettings.width; minimumWidth: 250
    height: applicationSettings.height; minimumHeight: 200
    x: applicationSettings.x
    y: applicationSettings.y
    visible: true

    onWidthChanged: applicationSettings.width = width
    onHeightChanged: applicationSettings.height = height
    onXChanged: applicationSettings.x = x
    onYChanged: applicationSettings.y = y
    onClosing: applicationSettings.saveApplicationSettings()

    SystemTrayIcon {
        visible: true
        iconSource: "qrc:/settings.svg"

        onActivated: {
            window.show()
            window.raise()
            window.requestActivate()
        }

        menu: Menu {
            MenuItem {
                text: qsTr("Quit")
                onTriggered: Qt.quit()
            }
        }
    }

    Shortcut {
        sequence: "Ctrl+1"
        onActivated: slideControl.slide = 0
    }

    Shortcut {
        sequence: "Ctrl+2"
        onActivated: slideControl.slide = 1
    }

    Shortcut {
        sequence: "Ctrl+3"
        onActivated: slideControl.slide = 2
    }

    SwipeView {
        id: qmlSwipeView
        anchors.fill: parent
        orientation: Qt.Horizontal
        currentIndex: slideControl.slide
        interactive: false
        onCurrentItemChanged: slideControl.slide = currentIndex

        LogIn {
            id: qmlLogIn
            onLogInClicked: slideControl.slide = 1
        }

        Dashboard {
            id: qmlDashboard
            onSettingsClicked: slideControl.slide = 2
        }

        Settings {
            id: qmlSettings
            onCloseClicked: slideControl.slide = 1
        }
    }
}

