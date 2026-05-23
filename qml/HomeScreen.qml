import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Page {
    title: qsTr("Homepage")
    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        SwipeView {
            id: swipeView
            Layout.fillWidth: true
            Layout.fillHeight: true
            currentIndex: tabBar.currentIndex //биндится с tabBar по индексу контента

            interactive: true // Включаем возможность листать свайпами
            // callback при свайпе обновляем TabBar
            onCurrentIndexChanged: {
                if (tabBar.currentIndex != currentIndex)
                    tabBar.currentIndex = currentIndex
            }

            MainContent {}
            Profile {}
            NewsScreen {}
        }

        TabBar {
            id: tabBar
            Layout.fillWidth: true
            TabButton {
                text: qsTr("Homepage")
            }
            TabButton {
                text: qsTr("Profile")
            }
            TabButton {
                text: qsTr("News")
            }
        }
    }

    footer: Button {
        text: "Выйти"
        anchors.centerIn: parent
        onClicked: AppContext.logout()
    }
}
