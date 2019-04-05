#include "kopiappsettings.h"
#include "kstyle.h"
#include "kopi.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtWebEngine>
//#include <QtWebView>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QtWebEngine::initialize();
//    QtWebView::initialize();
    QString settingsPath;

#ifdef Q_OS_MACOS
    settingsPath = "/Users/psaraci/mystuff/projects/kopi/kopi/kopisettingsssss";
#endif

#ifdef Q_OS_LINUX
    settingsPath = "/home/petref/mystuff/projects/kopi/kopi/kopisettings";
#endif

#ifdef Q_OS_IOS
    settingsPath = ":/kopisettings";
#endif

    KopiAppSettings::instance()->setSettingsPath(settingsPath);
    KopiAppSettings::instance()->readSettings();

    KStyle::instance()->init();
    Kopi::instance()->checkDefaultLocalStore();
    Kopi::instance()->readLocalStore();

    QQmlApplicationEngine qmlEngine;
    qmlEngine.load("qrc:/kopiapp/ui/qml/core/main.qml");

    return app.exec();
}
