import QtQuick
import QtQuick.Controls
import QtMultimedia

ApplicationWindow {
    width: 400
    height: 800
    visible: true
    title: "Camera App"
    color: "black"

    Column {
        anchors.centerIn: parent
        spacing: 20

        Text {
            text: "Приложение запущено!"
            color: "white"
            font.pixelSize: 24
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Button {
            text: "Нажми меня"
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: console.log("Кнопка нажата!")
        }
    }
}
