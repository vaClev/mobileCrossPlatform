import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material
import lesson0

PageWithBackButton {
    title: qsTr("Settings")

    // При уходе с экрана (назад, переход) закрываем соединение
    Component.onDestruction: AppContext.closeSettings()

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 20

        Label {
            text: qsTr("Appearence")
            font.pixelSize: 20
            font.bold: true
            Layout.alignment: Qt.AlignLeft
        }

        /// Переключатель цветовой темы
        RowLayout {
            Label {
                text: qsTr("Dark theme")
                font.pixelSize: 16
                Layout.fillWidth: true
            }
            Switch {
                id: themeSwitch
                checked: AppContext.isDarkTheme
                onCheckedChanged: AppContext.setDarkTheme(checked)
            }
        }

        /// Переключатель языка
        RowLayout {
            Label {
                text: qsTr("Language")
                font.pixelSize: 16
                Layout.fillWidth: true
            }
            Button {
                text: "RU"
                highlighted: AppContext && AppContext.language === "ru"
                onClicked: if (AppContext)
                               AppContext.setLanguage("ru")
            }
            Button {
                text: "EN"
                highlighted: AppContext && AppContext.language === "en"
                onClicked: if (AppContext)
                               AppContext.setLanguage("en")
            }
        }
        /// заполнитель "пружина"
        Item {
            Layout.fillHeight: true
        }
    }
}
