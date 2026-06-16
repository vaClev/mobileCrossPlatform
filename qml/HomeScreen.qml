import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Layouts
import lesson0

Page {
    title: qsTr("Homepage")

    header: ToolBar {
        background: Rectangle {
            color: AppContext.isDarkTheme ? Material.color(
                                                Material.Grey,
                                                Material.Shade900) : Material.color(
                                                Material.Grey,
                                                Material.Shade100)
        }
        RowLayout {
            anchors.fill: parent
            ToolButton {
                icon.source: "qrc:/assets/icons/menu.svg"
                icon.width: appWindow.iconSize
                icon.height: appWindow.iconSize
                onClicked: mainDrawer.open()
                icon.color: appWindow.textColor
            }
            Label {
                text: qsTr("Homepage")
                font.pixelSize: 18
                elide: Label.ElideRight
                Layout.fillWidth: true
                color: appWindow.textColor
            }
            Item {
                Layout.fillWidth: true
            }
        }
    }

    // Боковое меню - компонент MainDrawer
    MainDrawer {
        id: mainDrawer
        onMenuItemSelected: function (itemId) {
            switch (itemId) {
            case "profile":
                NavManager.navigateTo("profileEdit")
                break
            case "settings":
                NavManager.navigateTo("settings")
                break
            case "about":
                // TODO: показать информацию
                break
            case "logout":
                AppContext.logout()
                break
            }
        }
    }

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
}
