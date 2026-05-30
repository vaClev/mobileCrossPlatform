import QtQuick
import QtQuick.Controls
import lesson0

Page {
    title: qsTr("Home page")
    Label {
        anchors.centerIn: parent
        text: qsTr("Welcome!")
        font.pixelSize: 24
    }
}
