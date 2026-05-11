import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

ApplicationWindow {
    visible: true
    title: qsTr("User profile")
    minimumWidth: 320 // Минимальная ширина современных экранов телефонов
    minimumHeight: 480 // Комфортная высота с запасом. Если что прокрутят.

    // Единый тёмный стиль для всех платформ
    Material.theme: Material.Dark
    Material.accent: Material.Orange

    Page {
        anchors.fill: parent
        //anchors.margins: 20 // как вариант в пикселях
        // Внутренние отступы в процентах от размеров окна
        anchors.margins: Math.min(parent.width,
                                  parent.height) * 0.03 // 3% от меньшей стороны

        ColumnLayout {
            anchors.fill: parent
            spacing: 15

            //заголовок
            Label {
                text: qsTr("Fill profile")
                font.pixelSize: 22
                font.bold: true
                Layout.alignment: Qt.AlignCenter
            }

            // Поле ввода имени
            RowLayout {
                Label {
                    text: qsTr("Name:")
                    Layout.preferredWidth: 80
                }
                TextField {
                    id: nameField
                    placeholderText: qsTr("Enter your name")
                    Layout.fillWidth: true
                }
            }

            // Выбор возраста
            RowLayout {
                Label {
                    text: qsTr("Age:")
                    Layout.preferredWidth: 80
                }
                SpinBox {
                    id: ageSpinBox
                    from: 0
                    to: 120
                    value: 25
                }
            }

            // Получать уведомления
            RowLayout {
                Label {
                    text: qsTr("Notification:")
                    Layout.preferredWidth: 80
                }
                Switch {
                    id: notificationSwitch
                    checked: true
                }
            }

            //Уровень опыта
            GroupBox {
                title: qsTr("Expirience:")
                Layout.fillWidth: true
                Layout.minimumWidth: 300
                RowLayout {
                    anchors.fill: parent
                    RadioButton {
                        text: qsTr("Beginer")
                        checked: true
                        Layout.fillWidth: true
                    }
                    RadioButton {
                        text: qsTr("Middle")
                        Layout.fillWidth: true
                        Layout.alignment: Qt.AlignHCenter
                    }
                    RadioButton {
                        text: qsTr("Senior")
                        Layout.fillWidth: true
                    }
                }
            }

            //Кнопка сохранения
            Button {
                text: qsTr("Save profile")
                Layout.alignment: Qt.AlignHCenter
                Layout.topMargin: 10
                onClicked: {
                    //тут можно вызывать c++ методы нужных классов
                    // пока заглушка
                    console.log("Имя", nameField.text)
                    console.log("Возраст", ageSpinBox.value)
                    console.log("Уведомления", notificationSwitch.checked)
                }
            }

            // Растягивающийся элемент, чтобы всё не прилипало к верху
            Item {
                Layout.fillHeight: true
            }

            /// Переключатель языка
            Row {
                Layout.alignment: Qt.AlignHCenter
                spacing: 10
                Button {
                    text: "RU"
                    highlighted: languageManager.currentLanguage === "ru"
                    onClicked: languageManager.setLanguage("ru")
                }
                Button {
                    text: "EN"
                    highlighted: languageManager.currentLanguage === "en"
                    onClicked: languageManager.setLanguage("en")
                }
            }
        }
    }
}
