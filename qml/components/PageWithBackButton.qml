import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

Page {
    id: root

    // Свойство, позволяющее переопределить текст кнопки
    property alias backButtonText: backButton.text

    // Единый тёмный стиль для всех
    Material.theme: Material.Dark
    Material.accent: Material.Orange

    header: ToolBar {
        RowLayout {

            anchors.fill: parent
            ToolButton {
                id: backButton
                text: qsTr("← back")
                //visible: Qt.platform.os === "ios"
                onClicked: NavManager.goBack()
            }
            Item {
                Layout.fillWidth: true
            }
        }
    }

    // Контент страницы передаём сюда обычным образом, как дочерний элемент
    // Например: PageWithBackButton { Label { text: "Привет" } }
}
