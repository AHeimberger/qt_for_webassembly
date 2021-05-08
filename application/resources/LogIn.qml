import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.1
import QtQuick.Controls.Styles 1.4

Rectangle {
    id: qmlLogIn
    color: themeProvider.currentTheme.settings_background

    signal logInClicked()

    RowLayout {
        id: qmlLoginContainer
        anchors.centerIn: parent

        function sendText() {
            qmlLogIn.logInClicked(qmlTextField.text)
            applicationSettings.userName = qmlTextField.text;
            qmlTextField.text = "";
        }

        TextField {
            id: qmlTextField
            Layout.fillWidth: true
            placeholderText: qsTr("Username")
            onAccepted:  qmlLoginContainer.sendText()
        }

        ButtonIcon {
            source: icon_add
            // enabled: (qmlTextField.text.length !== 0)
            onClicked: qmlLoginContainer.sendText()
        }
    }
}
