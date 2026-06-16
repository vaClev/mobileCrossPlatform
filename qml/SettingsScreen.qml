import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material
import lesson0

PageWithBackButton {
    title: qsTr("Settings")

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
                highlighted: languageManager
                             && languageManager.currentLanguage === "ru"
                onClicked: if (languageManager)
                               languageManager.setLanguage("ru")
            }
            Button {
                text: "EN"
                highlighted: languageManager
                             && languageManager.currentLanguage === "en"
                onClicked: if (languageManager)
                               languageManager.setLanguage("en")
            }
        }
        /// заполнитель "пружина"
        Item {
            Layout.fillHeight: true
        }
    }
}
