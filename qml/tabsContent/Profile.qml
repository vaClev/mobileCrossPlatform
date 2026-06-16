import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material
import lesson0

Page {
    title: qsTr("Profile")

    ColumnLayout {
        anchors.centerIn: parent
        spacing: 15
        Label {
            text: qsTr("My Profile")
            font.pixelSize: 22
            Layout.alignment: Qt.AlignHCenter
        }
        Button {
            id: edit
            text: qsTr("Edit")
            onClicked: NavManager.navigateTo("profileEdit")
        }
    }
}
