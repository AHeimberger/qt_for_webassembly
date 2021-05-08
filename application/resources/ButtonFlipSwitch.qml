import QtQuick 2.0

Item {
    id: qmlButtonFlipSwitch
    property bool enabled: false

    Rectangle {
        anchors.verticalCenter: parent.verticalCenter
        width: 30
        height: 15
        radius: 10
        color: qmlButtonFlipSwitch.enabled ? "green" : "grey"

        Rectangle {
            width: 8
            height: 8
            x: qmlButtonFlipSwitch.enabled ? (parent.width - 13) : 5
            y: (parent.height/2 - height/2)
            radius: 5
        }
    }
}
