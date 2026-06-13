import QtQuick
import QtQuick.Controls
import lesson0

Page {
    title: qsTr("News")

    /// Контейнер в котором будут размещаться элементы списка
    ListView {
        id: newsList
        anchors.fill: parent
        anchors.margins: 10
        spacing: 8
        clip: true //Обрезка содержимого по границам

        model: newsModel ? newsModel : null //Связка с моделью которую отображаем

        /// описание одной карточки
        delegate: Rectangle {
            id: newsItem
            x: 10 // отступ слева
            width: ListView.view.width - 20 // ширина с учётом отступов с обеих сторон
            height: 100
            radius: 8
            color: "#2c2c2c"

            Column {
                anchors.fill: parent
                anchors.margins: 12
                spacing: 4

                Text {
                    text: model.title
                    color: "white"
                    font.pixelSize: 16
                    font.bold: true
                    elide: Text.ElideRight
                    width: parent.width
                }

                Text {
                    text: model.date
                    color: "#aaaaaa"
                    font.pixelSize: 12
                }

                Text {
                    text: model.summary
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
                    //имена полей определены  NewsListModel::roleNames()
                    console.log("Новость #" + model.newsId + ": " + model.title)
                    // Позже: NavManager.navigateTo("newsDetail") с передачей данных
                }
            }
        }

        // Разделитель между элементами (опционально)
        ScrollBar.vertical: ScrollBar {
            policy: ScrollBar.AsNeeded
        }

        // футер с индикатором загрузки.
        footer: Item {
            width: ListView.view.width
            height: newsModel && newsModel.isLoading ? 60 : 0
            visible: newsModel && newsModel.isLoading
            clip: true

            BusyIndicator {
                anchors.centerIn: parent
                running: newsModel && newsModel.isLoading
            }
        }
    }

    // Кнопка для "принудительного обновления" (имитация запроса к серверу)
    RoundButton {
        text: "⟳"
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.margins: 16
        enabled: newsModel
                 && !newsModel.isLoading // неактивна во время загрузки
        onClicked: if (newsModel)
                       newsModel.fetchNews()
    }

    // Пока нет новостей — сообщение
    Label {
        anchors.centerIn: parent
        text: qsTr("Новостей пока нет")
        color: "#888888"
        visible: !newsModel || newsModel.count === 0
    }
}
