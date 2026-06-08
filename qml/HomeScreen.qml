import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import lesson0

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
                icon.source: "qrc:/assets/icons/home.svg"
                icon.width: appWindow.iconSizeSecond
                icon.height: appWindow.iconSizeSecond
                text: qsTr("Homepage")
                display: AbstractButton.TextUnderIcon
            }
            TabButton {
                icon.source: "qrc:/assets/icons/profile.svg"
                icon.width: appWindow.iconSizeSecond
                icon.height: appWindow.iconSizeSecond
                text: qsTr("Profile")
                display: AbstractButton.TextUnderIcon
            }
            TabButton {
                icon.source: "qrc:/assets/icons/news.svg"
                icon.width: appWindow.iconSizeSecond
                icon.height: appWindow.iconSizeSecond
                text: qsTr("News")
                display: AbstractButton.TextUnderIcon
            }
        }
    }

    footer: Button {
        id: exit
        text: qsTr("Exit")
        onClicked: AppContext.logout()
    }
}
