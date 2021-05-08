import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.1
import QtQuick.Controls.Styles 1.4

Rectangle {
    id: qmlDashboard
    color: themeProvider.currentTheme.settings_background

    signal settingsClicked()

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        Spacer { Layout.fillWidth: true; Layout.preferredHeight: 10 }

        RowLayout {
            Layout.fillWidth: true
            spacing: 0

            Spacer { Layout.preferredWidth: 10 }

            Text {
                text: (applicationSettings.userName == "") ? qsTr("Dashboard") :  qsTr("Hey, %1").arg(applicationSettings.userName)
                font.bold: true
                color: themeProvider.currentTheme.settings_text
                Layout.fillWidth: true
            }

            Spacer { Layout.preferredWidth: 10 }

            ButtonIcon {
                source: icon_settings
                onClicked: qmlDashboard.settingsClicked()
            }

            Spacer { Layout.preferredWidth: 10 }
        }

        Spacer {  Layout.fillWidth: true; Layout.preferredHeight: 10 }

        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true

            Flickable {
                anchors.fill: parent
                anchors.topMargin: 5
                anchors.leftMargin: 5
                anchors.rightMargin: 5
                anchors.bottomMargin: 5
                contentHeight: grid.height
                contentWidth: parent.width
                flickableDirection: Flickable.VerticalFlick
                clip: true

                GridLayout {
                    id: grid
                    columns: (parent.width > 500) ? 2 : 1
                    columnSpacing: 5
                    rowSpacing: 5
                    anchors.margins: 5
                    width: parent.width
                    height: implicitHeight

                    Rectangle {
                        Layout.columnSpan: parent.columns
                        Layout.fillWidth: true
                        Layout.preferredHeight: 100
                        color: "lightgrey"

                        RowLayout {
                            id: qmlMessageContainer
                            anchors.centerIn: parent

                            function sendText() {
                                dataProvider.sendMessage(qmlTextField.text)
                                qmlTextField.text = ""
                            }

                            TextField {
                                id: qmlTextField
                                Layout.fillWidth: true
                                placeholderText: qsTr("Your Message")
                                onAccepted: qmlMessageContainer.sendText()
                            }

                            ButtonIcon {
                                source: icon_add
                                onClicked: qmlMessageContainer.sendText()
                            }
                        }
                    }

                    Repeater {
                        model: valuesList
                        delegate:
                            Item {
                            Layout.fillWidth: true
                            Layout.preferredHeight: 100

                            Loader {
                                anchors.fill: parent
                                sourceComponent: {
                                    switch(representation) {
                                    case "text": return qmlText;
                                    case "circleprogress": return qmlCircleProgress;
                                    case "led": return qmlLed;
                                    case "humidity": return qmlHumidity;
                                    case "pressure": return qmlPressure;
                                    case "temperature": return qmlTemperature;
                                    }

                                    return qmlText;
                                }

                                Component {
                                    id: qmlText

                                    Rectangle {
                                        width: 50
                                        height: 50
                                        color: "lightgrey"

                                        Text {
                                            width: 150
                                            anchors.centerIn: parent
                                            horizontalAlignment: Text.AlignHCenter
                                            text: qsTr("%1 %2\n%3").arg(currentValue).arg(unit).arg(name)
                                        }
                                    }
                                }

                                Component {
                                    id: qmlCircleProgress

                                    Rectangle {
                                        width: 50
                                        height: 50
                                        color: "lightgrey"

                                        Text {
                                            anchors.centerIn: parent
                                            horizontalAlignment: Text.AlignHCenter
                                            text: qsTr("%1 %5").arg(currentValue).arg(unit)
                                        }

                                        Item {
                                            id: progress
                                            anchors.fill: parent
                                            anchors.margins: 30

                                            Progress {
                                                width: (parent.width > parent.height) ? parent.height : parent.width
                                                height: width
                                                anchors.centerIn: parent
                                                arcBegin: 0
                                                arcEnd: 360 * currentValue
                                                lineWidth: 5
                                                lineColor: "#222222"
                                                onArcEndChanged: requestPaint()
                                            }
                                        }

                                        Text {
                                            anchors.top: progress.bottom
                                            anchors.topMargin: 5
                                            width: parent.width
                                            horizontalAlignment: Text.AlignHCenter
                                            text: name
                                        }
                                    }
                                }

                                Component {
                                    id: qmlLed

                                    Rectangle {
                                        width: 50
                                        height: 50
                                        color: "lightgrey"

                                        Rectangle {
                                            id: led
                                            anchors.centerIn: parent
                                            width: 20; height: 20; radius: 20
                                            color: currentValue ? "blue" : "red"
                                        }

                                        Text {
                                            width: parent.width
                                            horizontalAlignment: Text.AlignHCenter
                                            anchors.top: led.bottom
                                            anchors.topMargin: 5
                                            text: name
                                        }
                                    }
                                }

                                Component {
                                    id: qmlHumidity

                                    Rectangle {
                                        Layout.fillWidth: true
                                        Layout.preferredHeight: 100
                                        color: "lightgray"


                                        RowLayout {
                                            anchors.fill: parent

                                            Rectangle {
                                                Layout.fillWidth: true
                                                Layout.fillHeight: true
                                                color: "#222222"

                                                Image {
                                                    anchors.centerIn: parent
                                                    sourceSize.width: 50
                                                    sourceSize.height: 50
                                                    source: "qrc:/resources/icons/humidity.svg"
                                                }
                                            }

                                            Item {
                                                Layout.fillWidth: true
                                                Layout.fillHeight: true

                                                Column {
                                                    anchors.centerIn: parent
                                                    spacing: 5

                                                    Text {
                                                        font.pixelSize: 20
                                                        anchors.horizontalCenter: parent.horizontalCenter
                                                        text: qsTr("%1 %5").arg(currentValue).arg(unit)
                                                    }

                                                    Rectangle {
                                                        width: parent.width
                                                        height: 2
                                                        color: "black"
                                                    }

                                                    Text {
                                                        anchors.horizontalCenter: parent.horizontalCenter
                                                        text: name
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }

                                Component {
                                    id: qmlPressure

                                    Rectangle {
                                        Layout.fillWidth: true
                                        Layout.preferredHeight: 100
                                        color: "lightgray"


                                        RowLayout {
                                            anchors.fill: parent

                                            Rectangle {
                                                Layout.fillWidth: true
                                                Layout.fillHeight: true
                                                color: "#222222"

                                                Image {
                                                    anchors.centerIn: parent
                                                    sourceSize.width: 50
                                                    sourceSize.height: 50
                                                    source: "qrc:/resources/icons/pressure.svg"
                                                }
                                            }

                                            Item {
                                                Layout.fillWidth: true
                                                Layout.fillHeight: true

                                                Column {
                                                    anchors.centerIn: parent
                                                    spacing: 5

                                                    Text {
                                                        font.pixelSize: 20
                                                        anchors.horizontalCenter: parent.horizontalCenter
                                                        text: qsTr("%1 %5").arg(currentValue).arg(unit)
                                                    }

                                                    Rectangle {
                                                        width: parent.width
                                                        height: 2
                                                        color: "black"
                                                    }

                                                    Text {
                                                        anchors.horizontalCenter: parent.horizontalCenter
                                                        text: name
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }

                                Component {
                                    id: qmlTemperature

                                    Rectangle {
                                        Layout.fillWidth: true
                                        Layout.preferredHeight: 100
                                        color: "lightgray"

                                        RowLayout {
                                            anchors.fill: parent

                                            Rectangle {
                                                Layout.fillWidth: true
                                                Layout.fillHeight: true
                                                color: "#222222"

                                                Image {
                                                    anchors.centerIn: parent
                                                    sourceSize.width: 50
                                                    sourceSize.height: 50
                                                    source: "qrc:/resources/icons/temperature.svg"
                                                }
                                            }

                                            Item {
                                                Layout.fillWidth: true
                                                Layout.fillHeight: true

                                                Column {
                                                    anchors.centerIn: parent
                                                    spacing: 5

                                                    Text {
                                                        font.pixelSize: 20
                                                        anchors.horizontalCenter: parent.horizontalCenter
                                                        text: qsTr("%1 %5").arg(currentValue).arg(unit)
                                                    }

                                                    Rectangle {
                                                        width: parent.width
                                                        height: 2
                                                        color: "black"
                                                    }

                                                    Text {
                                                        anchors.horizontalCenter: parent.horizontalCenter
                                                        text: name
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
