import QtQuick
import QtQuick.Controls
import lesson0

ApplicationWindow {
    id: appWindow
    visible: true
    title: "Mobile App"

    // Свойство доступно всем дочерним элементам - размер иконок
    property int iconSizePrimary: font.pixelSize * 1.5
    property int iconSizeSecond: font.pixelSize * 2

    ///////////////////////////////////////////
    // Корневой фокусируемый контейнер для перехвата событий нажатия на кнопки на корпусе телефона
    Item {
        anchors.fill: parent
        focus: true

        ///////////////////////////////////////////
        // Единый тёмный стиль для всех
        Material.theme: Material.Dark
        Material.accent: Material.Orange

        ///////////////////////////////////////////
        // Обработчик нажатия кнопки "назад" - Android: на ios просто не сработает
        Keys.onBackPressed: {
            console.log("Back pressed!")
            NavManager.goBack()
            // Событие не дойдёт до системы, приложение не закроется
        }

        ///////////////////////////////////////////
        // Главный StackView приложения
        StackView {
            id: mainStackView
            anchors.fill: parent
            initialItem: loginScreen // Начинаем с экрана входа
        }

        ///////////////////////////////////////////
        // Все компоненты входящие в StackView описываются ниже
        // для них подключен модуль "import lesson0"
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
    }

    ///////////////////////////////////////////
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
            console.log("back requested")
            if (mainStackView.depth > 1) {
                //на ios была проблема с pop(), проверить потом.
                mainStackView.pop()

                //mainStackView.currentItem.visible = false
                //mainStackView.replace(homeScreen)
            } else {
                NavManager.minimizeApp() // сворачиваем приложение
            }
        }
    }

    ///////////////////////////////////////////
    // Реакция на изменение статуса авторизации
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
