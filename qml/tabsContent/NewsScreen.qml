import QtQuick
import QtQuick.Controls
import lesson0

Page {
    title: qsTr("News")

    // Модель данных (пока "встроенная")
    /// По сути например список полученный с сервера
    ListModel {
        id: newsModel
        ListElement {
            title: "Вышла Qt 6.9"
            date: "12 июня 2026"
            summary: "Релиз с новыми возможностями для мобильной разработки."
        }
        ListElement {
            title: "Обновление Android 16"
            date: "10 июня 2026"
            summary: "Google анонсировала Android 16 Beta 3."
        }
        ListElement {
            title: "WWDC 2026"
            date: "5 июня 2026"
            summary: "Apple представила новые инструменты для разработчиков."
        }
        ListElement {
            title: "Советы по QML"
            date: "1 июня 2026"
            summary: "10 советов по оптимизации ListView."
        }
        ListElement {
            title: "Кроссплатформенная разработка"
            date: "28 мая 2026"
            summary: "Сравнение Flutter, React Native и Qt Quick."
        }
    }

    /// Контейнер в котором будут размещаться элементы списка
    ListView {
        id: newsList
        anchors.fill: parent
        anchors.margins: 10
        spacing: 8
        clip: true //Обрезка содержимого по границам

        model: newsModel //Связка с моделью которую отображаем

        /// описание одной карточки
        delegate: Rectangle {
            id: newsItem
            width: ListView.view.width - 20
            height: 100
            radius: 8
            color: "#2c2c2c"
            anchors.horizontalCenter: parent.horizontalCenter

            Column {
                anchors.fill: parent
                anchors.margins: 12
                spacing: 4

                Text {
                    text: title
                    color: "white"
                    font.pixelSize: 16
                    font.bold: true
                    elide: Text.ElideRight
                    width: parent.width
                }

                Text {
                    text: date
                    color: "#aaaaaa"
                    font.pixelSize: 12
                }

                Text {
                    text: summary
                    color: "#cccccc"
                    font.pixelSize: 13
                    elide: Text.ElideRight
                    maximumLineCount: 2
                    width: parent.width
                }
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    console.log("Новость:", title)
                    // Позже: NavManager.navigateTo("newsDetail") с передачей данных
                }
            }
        }

        // Разделитель между элементами (опционально)
        ScrollBar.vertical: ScrollBar {
            policy: ScrollBar.AsNeeded
        }
    }

    // Пока нет новостей — сообщение
    Label {
        anchors.centerIn: parent
        text: qsTr("Новостей пока нет")
        color: "#888888"
        visible: newsModel.count === 0
    }
}
