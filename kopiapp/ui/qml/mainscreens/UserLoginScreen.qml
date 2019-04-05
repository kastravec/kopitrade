import QtQuick 2.12

import Kopi 1.0

UserLoginScreenForm {
    id: root

    signal signedInSuccess
    signal registerRequest

    loginBox.backgroundColor: KStyle.styleDefinition.kspecs.mainMenu.mainBox.background.color
    registerButton.backgroundColor: KStyle.styleDefinition.kspecs.mainMenu.mainBox.background.color
    demoAccountButton.backgroundColor: KStyle.styleDefinition.kspecs.mainMenu.mainBox.background.color

    KopiUser {
        id: loginUser

        onStatusChanged: {
            if (loginUser.status === KopiUser.SignedIn) {
                root.statusLabel.text = qsTr("Signed in successfully!")
                root.signedInSuccess()
            } else if (loginUser.status === KopiUser.ErrorSignIn) {
                root.statusLabel.text = loginUser.lastErrorString
            }
            root.busyIndicator.running = false
        }
    }

    registerButton.onClicked: root.registerRequest()

    loginButton.onClicked: {
        if (usernameInput.text.length > 2 && passwordInput.text.length > 2) {
            root.busyIndicator.running = true
            root.statusLabel.text = "Signing in..."
            loginUser.signIn(usernameInput.text, passwordInput.text)
        } else {
            root.statusLabel.text = qsTr("Enter a valid email and password..")
        }
    }

    demoAccountButton.onClicked: {
        signedInSuccess()
    }

    usernameInput.onTextChanged: root.statusLabel.text = ""
    passwordInput.onTextChanged: root.statusLabel.text = ""
}
