import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    width: 400
    height: 800
    visible: true
    title: "User profile"

    // Единый тёмный стиль для всех платформ
    Material.theme: Material.Dark
    Material.accent: Material.Orange

    Page {
        anchors.fill: parent
        anchors.margins: 20

        ColumnLayout {
            anchors.fill: parent
            spacing: 15

            //заголовок
            Label {
                text: "Заполните профиль"
                font.pixelSize: 22
                font.bold: true
                Layout.alignment: Qt.AlignCenter
            }

            // Поле ввода имени
            RowLayout {
                Label {
                    text: "имя:"
                    Layout.preferredWidth: 80
                }
                TextField {
                    id: nameField
                    placeholderText: "Введите имя"
                    Layout.fillWidth: true
                }
            }

            // Выбор возраста
            RowLayout {
                Label {
                    text: "Возраст:"
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
                    text: "Уведомления:"
                    Layout.preferredWidth: 80
                }
                Switch {
                    id: notificationSwitch
                    checked: true
                }
            }

            //Уровень опыта
            GroupBox {
                title: "Уровень опыта"
                Layout.fillWidth: true
                RowLayout {
                    RadioButton {
                        text: "начинающий"
                        checked: true
                    }
                    RadioButton {
                        text: "Middle"
                    }
                    RadioButton {
                        text: "Senior"
                    }
                }
            }

            //Кнопка сохранения
            Button {
                text: "Сохранить профиль"
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
        }
    }
}
