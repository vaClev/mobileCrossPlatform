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
            placeholderText: "Login"
        }
        TextField {
            id: passField
            placeholderText: "Password"
            echoMode: TextInput.Password
        }
        Button {
            text: "Log in"
            onClicked: AppContext.login(loginField.text, passField.text)
            // NavigationManager среагирует на сигнал AppContext.authStateChanged и переключит экран
        }

        Button {
            text: "Check"
            onClicked: console.log("Auth state:", AppContext.isAuthenticated)
        }
    }
}
