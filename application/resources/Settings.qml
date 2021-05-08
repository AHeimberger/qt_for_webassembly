import QtQuick 2.0
import QtQuick.Layouts 1.1


Rectangle {
    id: qmlSettings
    color: themeProvider.currentTheme.settings_background

    signal closeClicked()

    ColumnLayout {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 10
        spacing: 0

        Spacer { Layout.fillWidth: true; Layout.preferredHeight: 10 }

        RowLayout {
            Layout.fillWidth: true
            spacing: 0

            Spacer { Layout.preferredWidth: 10 }

            Text {
                text: "Settings"
                font.bold: true
                color: themeProvider.currentTheme.settings_text
                Layout.fillWidth: true
            }

            Spacer { Layout.preferredWidth: 10 }

            ButtonIcon {
                source: icon_close
                onClicked: qmlSettings.closeClicked()
            }

            Spacer { Layout.preferredWidth: 10 }
        }

        Spacer { Layout.fillWidth: true; Layout.preferredHeight: 10 }

        Flickable {
            Layout.fillWidth: true
            Layout.fillHeight: true

            ColumnLayout {
                width: parent.width

                Rule { Layout.fillWidth: true; Layout.preferredHeight: 1 }

                Item {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 30

                    RowLayout {
                        anchors.fill: parent
                        anchors.margins: 10

                        Text {
                            Layout.preferredWidth: 100
                            text: "Date"
                            elide: Text.ElideMiddle
                            wrapMode: Text.NoWrap
                            color: themeProvider.currentTheme.settings_text
                        }

                        TextInput {
                            text: applicationSettings.dateTimeFormat
                            Layout.fillWidth: true
                            wrapMode: Text.NoWrap
                            onTextChanged: applicationSettings.dateTimeFormat = text
                            color: themeProvider.currentTheme.settings_text
                        }
                    }

                    Rule { width: parent.width; height: 1; anchors.bottom: parent.bottom }
                }

                Item {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 30

                    RowLayout {
                        anchors.fill: parent
                        anchors.margins: 10

                        Text {
                            Layout.preferredWidth: 100
                            text: "Theme"
                            elide: Text.ElideMiddle
                            wrapMode: Text.NoWrap
                            color: themeProvider.currentTheme.settings_text
                        }

                        Text {
                            Layout.fillWidth: true
                            text: themeProvider.currentThemeName
                            color: themeProvider.currentTheme.settings_text
                        }
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: themeProvider.changeTheme();
                    }

                    Rule { width: parent.width; height: 1; anchors.bottom: parent.bottom }
                }

                Item {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 30

                    RowLayout {
                        anchors.fill: parent
                        anchors.margins: 10

                        Text {
                            Layout.preferredWidth: 100
                            text: "IP"
                            elide: Text.ElideMiddle
                            wrapMode: Text.NoWrap
                            color: themeProvider.currentTheme.settings_text
                        }

                        TextInput {
                            text: applicationSettings.ip
                            Layout.fillWidth: true
                            wrapMode: Text.NoWrap
                            onTextChanged: applicationSettings.ip = text
                            color: themeProvider.currentTheme.settings_text
                        }
                    }

                    Rule { width: parent.width; height: 1; anchors.bottom: parent.bottom }
                }

                Spacer { Layout.fillWidth: true; Layout.preferredHeight: 30 }

                Item {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 30

                    Text {
                        text: "Information"
                        font.bold: true
                        anchors.fill: parent
                        anchors.margins: 10
                        color: themeProvider.currentTheme.settings_text
                    }

                    Rule { width: parent.width; height: 1; anchors.bottom: parent.bottom }
                }

                Item {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 30

                    RowLayout {
                        anchors.fill: parent
                        anchors.margins: 10

                        Text {
                            Layout.preferredWidth: 100
                            text: "Version"
                            elide: Text.ElideMiddle
                            wrapMode: Text.NoWrap
                            color: themeProvider.currentTheme.settings_text
                        }

                        Text {
                            Layout.fillWidth: true
                            text: Qt.application.version
                            elide: Text.ElideLeft
                            wrapMode: Text.NoWrap
                            color: themeProvider.currentTheme.settings_text
                        }
                    }

                    Rule { width: parent.width; height: 1; anchors.bottom: parent.bottom }
                }

                Spacer { Layout.fillWidth: true; Layout.preferredHeight: 30 }

                Item {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 30

                    Text {
                        text: "Values"
                        font.bold: true
                        anchors.fill: parent
                        anchors.margins: 10
                        color: themeProvider.currentTheme.settings_text
                    }

                    Rule { width: parent.width; height: 1; anchors.bottom: parent.bottom }
                }

                Column {
                    Layout.fillWidth: true

                    Repeater {
                        model: valuesList
                        delegate:
                            Item {
                            width: parent.width
                            height: 30

                            RowLayout {
                                anchors.fill: parent
                                anchors.margins: 10

                                Text {
                                    Layout.fillWidth: true
                                    text: name
                                    elide: Text.ElideMiddle
                                    wrapMode: Text.NoWrap
                                    color: themeProvider.currentTheme.settings_text
                                }

                                Text {
                                    Layout.preferredWidth: 50
                                    text: currentValue
                                    horizontalAlignment: Text.AlignRight
                                    color: themeProvider.currentTheme.settings_text
                                }

                                Text {
                                    Layout.preferredWidth: 25
                                    text: unit
                                    horizontalAlignment: Text.AlignLeft
                                    color: themeProvider.currentTheme.settings_text
                                }
                            }

                            Rule { width: parent.width; height: 1; anchors.bottom: parent.bottom }
                        }
                    }
                }
            }
        }
    }
}
