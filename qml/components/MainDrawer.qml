import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Layouts

Drawer {
    id: root
    // 0,8 от ширины узкого экрана телефона. Или просто 500 пикселей - на компе
    width: Math.min(parent.width * 0.8, 500)
    height: parent.height
    edge: Qt.LeftEdge //слевой стороны экрана

    //background: Rectangle {
    //    color: "#2c2c2c"
    //}

    // Сигнал, который сообщает, какой пункт выбран
    signal menuItemSelected(string itemId)
    // этот сигнал испускает каждый элемент меню в onClicked
    ///////////////////////////////////////////////

    /// Отображаемые пункты всплывающего меню
    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 15

        Label {
            text: qsTr("Menu")
            font.pixelSize: 24
            font.bold: true
            color: appWindow.textColor
            Layout.alignment: Qt.AlignHCenter
        }

        Button {
            text: qsTr("Profile")
            flat: true
            contentItem: Text {
                text: parent.text
                color: appWindow.textColor
                font.pixelSize: 16
                horizontalAlignment: Text.AlignLeft
            }
            Layout.fillWidth: true
            onClicked: {
                root.close()
                root.menuItemSelected("profile")
            }
        }

        Button {
            text: qsTr("Settings")
            flat: true
            contentItem: Text {
                text: parent.text
                color: appWindow.textColor
                font.pixelSize: 16
                horizontalAlignment: Text.AlignLeft
            }
            Layout.fillWidth: true
            onClicked: {
                root.close()
                root.menuItemSelected("settings")
            }
        }

        Button {
            text: qsTr("About")
            flat: true
            contentItem: Text {
                text: parent.text
                color: appWindow.textColor
                font.pixelSize: 16
                horizontalAlignment: Text.AlignLeft
            }
            Layout.fillWidth: true
            onClicked: {
                root.close()
                root.menuItemSelected("about")
            }
        }

        Item {
            Layout.fillHeight: true
        }

        Button {
            text: qsTr("Logout")
            flat: true
            contentItem: Text {
                text: parent.text
                color: "#ff6b6b"
                font.pixelSize: 16
                horizontalAlignment: Text.AlignLeft
            }
            Layout.fillWidth: true
            onClicked: {
                root.close()
                root.menuItemSelected("logout")
            }
        }
        Button {
            text: qsTr("Close Application")
            flat: true
            contentItem: Text {
                text: parent.text
                color: "#ff6b6b"
                font.pixelSize: 16
                horizontalAlignment: Text.AlignLeft
            }
            Layout.fillWidth: true
            onClicked: {
                root.close()
                NavManager.shutdownApp()
            }
        }
    }
}
