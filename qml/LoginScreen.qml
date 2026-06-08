import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Page {
    title: qsTr("LoginScreen")
    ColumnLayout {
        anchors.centerIn: parent
        spacing: 10
        TextField {
            id: loginField
            placeholderText: qsTr("Login")
        }
        TextField {
            id: passField
            placeholderText: qsTr("Password")
            echoMode: TextInput.Password
        }
        Button {
            text: "Log in"
            onClicked: AppContext.login(loginField.text, passField.text)
            // NavigationManager среагирует на сигнал AppContext.authStateChanged и переключит экран
        }

        Button {
            text: "Check"
            visible: false //Включить можно для отладки если хочется
            onClicked: console.log("Auth state:", AppContext.isAuthenticated)
        }
    }
}
