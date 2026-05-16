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
            currentIndex: tabBar.currentIndex
            interactive: true // Включаем возможность листать свайпами

            //MainContent {}
            //Profile {}
            //NewsScreen {}
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
