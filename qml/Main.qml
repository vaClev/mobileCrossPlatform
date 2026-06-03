import QtQuick
import QtQuick.Controls
import lesson0

ApplicationWindow {
    id: appWindow
    visible: true
    title: "Mobile App"

    // Корневой фокусируемый контейнер для перехвата событий нажатия на кнопки на корпусе телефона
    Item {
        anchors.fill: parent
        focus: true

        Keys.onBackPressed: {
            console.log("Back pressed!")
            // Здесь вызываем вашу логику: NavManager.goBack()
            // Событие не дойдёт до системы, приложение не закроется
        }

        // Все ваши остальные элементы (StackView, кнопка и т.д.) помещаются сюда
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
                    mainStackView.push(
                                profileEditScreen) // ← кладём поверх стека
                }
            }

            function onBackRequested() {
                console.log("back requested")
                if (mainStackView.depth > 1) {
                    //на ios была проблема с pop(), проверить потом.
                    mainStackView.pop()
                    //mainStackView.currentItem.visible = false
                    //mainStackView.replace(homeScreen)
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
}
