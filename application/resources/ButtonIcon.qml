import QtQuick 2.0

Item {
    id: button
    width: 25; height: 25;

    readonly property string icon_add: "qrc:/resources/icons/add.svg"
    readonly property string icon_close: "qrc:/resources/icons/close.svg"
    readonly property string icon_settings: "qrc:/resources/icons/settings.svg"

    property alias source: qmlImage.source

    signal clicked()

    Image {
        id: qmlImage
        anchors.centerIn: parent
        state: "static"
        source: "qrc:/resources/icons/none.svg"
    }

    MouseArea {
        id: qmlMouseArea
        hoverEnabled: true
        anchors.fill: parent
        onClicked: button.clicked()
    }
}
