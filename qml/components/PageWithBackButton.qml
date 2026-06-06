import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

Page {
    id: root
    // Свойство, позволяющее переопределить текст кнопки
    property string backButtonText: qsTr("← back")

    // Header активен только на iOS – на Android Loader не создаёт ничего
    header: Loader {
        active: Qt.platform.os === "ios"
        sourceComponent: backToolBar
    }

    // Компонент тулбар для хеддера
    Component {
        id: backToolBar
        ToolBar {
            RowLayout {
                anchors.fill: parent
                ToolButton {
                    text: root.backButtonText
                    onClicked: NavManager.goBack()
                }
                Item {
                    Layout.fillWidth: true
                }
            }
        }
    }

    // Контент страницы передаём сюда обычным образом, как дочерний элемент
    // Например: PageWithBackButton { Label { text: "Привет" } }
}
