import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material
import lesson0

Page {
    title: qsTr("Profile")
    Material.theme: Material.Dark
    Material.accent: Material.Orange

    ColumnLayout {
        anchors.centerIn: parent
        spacing: 15
        Label {
            text: qsTr("My Profile")
            font.pixelSize: 22
            Layout.alignment: Qt.AlignHCenter
        }
        Button {
            text: qsTr("Edit")
            Layout.alignment: Qt.AlignHCenter
            onClicked: NavManager.navigateTo("profileEdit")
        }
    }
}
