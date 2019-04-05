import QtQuick 2.12

import Kopi 1.0

UserRegistrationScreenForm {
    id: root

    signal canceled
    signal registered
    signal demoPressed

    registrationBox.backgroundColor: KStyle.styleDefinition.kspecs.mainMenu.mainBox.background.color
    registerButton.backgroundColor: KStyle.styleDefinition.kspecs.mainMenu.mainBox.background.color
    demoAccountButton.backgroundColor: KStyle.styleDefinition.kspecs.mainMenu.mainBox.background.color

    cancelButton.onClicked: root.canceled()

    KopiUser {
        id: kopiuser
        userCredentials: {
            "username": usernameInput.text,
            "email": emailInput.text
        }

        onStatusChanged: {
            if (kopiuser.status === KopiUser.ErrorRegistering) {
                root.statusLabel.text = kopiuser.lastErrorString
                registrationBox.enabled = true
                busyIndicator.running = false
            } else if (kopiuser.status === KopiUser.Registered) {
                root.statusLabel.text = qsTr(
                            "User ") + usernameInput.text + " is registered!"
                root.registrationBox.enabled = false
                root.registered()
                busyIndicator.running = false
            }
        }
    }

    registerButton.onClicked: {
        if (usernameInput.text.length > 6 && passwordInput.text.length > 6) {
            root.busyIndicator.running = true
            root.statusLabel.text = "Registering your account..."
            registrationBox.enabled = false
            kopiuser.registerMe(passwordInput.text)
        } else {
            root.statusLabel.text = qsTr("Enter a valid email and password!")
        }
    }

    demoAccountButton.onClicked: root.demoPressed()

    usernameInput.onTextChanged: root.statusLabel.text = ""
    emailInput.onTextChanged: root.statusLabel.text = ""
    passwordInput.onTextChanged: root.statusLabel.text = ""
}
