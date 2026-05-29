import QtQuick
import QtQuick.Controls
import lesson0

ApplicationWindow {
    id: appWindow
    visible: true
    width: 360
    height: 640
    title: "Mobile App"

    StackView {
        id: mainStackView
        anchors.fill: parent
        initialItem: loginScreen // Начинаем с экрана входа
    }

    Component {
        id: loginScreen
        LoginScreen {}
    }
    Component {
        id: homeScreen
        HomeScreen {}
    }
    Component {
        id: profileEditScreen
        ProfileEditScreen {}
    }

    // Обработка сигналов от NavigationManager
    Connections {
        target: NavManager

        function onNavigationRequested(screenId) {
            if (screenId === "home") {
                // Заменяем весь стек, чтобы нельзя было вернуться на логин
                mainStackView.replace(homeScreen)
            } else if (screenId === "profileEdit") {

                mainStackView.push(profileEditScreen) // ← кладём поверх стека
            }
        }

        function onBackRequested() {
            if (mainStackView.depth > 1) {
                mainStackView.pop()
            }
        }
    }

    // Реакция на изменение статуса авторизации (когда-нибудь пригодится)
    Connections {
        target: AppContext

        function onAuthenticationStateChanged() {
            if (AppContext.isAuthenticated) {
                NavManager.navigateTo("home")
            } else {
                mainStackView.clear()
                mainStackView.push(loginScreen)
            }
        }
    }
}
