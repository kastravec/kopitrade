import QtQuick 2.12
import QtQuick.Window 2.2

import Kopi 1.0
import "../basickontrols"

Window {
    id: splash

    color: "transparent"
    modality: Qt.ApplicationModal
    flags: Qt.SplashScreen

    property int timeoutInterval: KopiAppSettings.settings.splashscreen_timeout
    signal timeout

    Component.onCompleted: visible = true

    x: (Screen.width - logoimage.width) / 2
    y: (Screen.height - logoimage.height) / 2

    width: logoimage.width
    height: logoimage.height

    KopiTradeLogo {
        width: 600
        height: 400
        id: logoimage
        logoFileName: "Color logo with background.png"
    }

    //! [timer]
    Timer {
        interval: timeoutInterval
        running: true
        repeat: false
        onTriggered: {
            visible = false
            splash.timeout()
        }
    }
}
