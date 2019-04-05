#include "kopiappsettings.h"

#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QJsonDocument>
#include <QSysInfo>

#include <QDebug>

class KopiAppSettings::Private
{
public:
    int platform, settingsStatus;
    QString settingsFilePath, graphicsAssetsPath, stylesPath;
    QJsonObject settings;
};

KopiAppSettings *KopiAppSettings::m_instance = nullptr;
KopiAppSettings *KopiAppSettings::instance()
{
    if(m_instance == nullptr)
        m_instance = new KopiAppSettings;

    return m_instance;
}

KopiAppSettings::KopiAppSettings(QObject *parent)
    :QObject(parent)
    ,m_data(new Private)
{
    updatePlatform();
    setSettingsStatus(Unkown);
}

KopiAppSettings::~KopiAppSettings()
{
    delete m_data;
    m_data = nullptr;
}

int KopiAppSettings::platform()
{
    return m_data->platform;
}

int KopiAppSettings::settingsStatus() const
{
    return m_data->settingsStatus;
}

void KopiAppSettings::setSettingsStatus(int status)
{
    if(m_data->settingsStatus != status) {
        m_data->settingsStatus =status;
        emit settingsStatusChanged(status);
    }
}

QString KopiAppSettings::settingsPath() const
{
    return m_data->settingsFilePath;
}

void KopiAppSettings::setSettingsPath(const QString &path)
{
    QString settingspath;

    if(path.isEmpty() || !QFile::exists(path)) {
        settingspath = ":/kopisettings";
    } else
        settingspath = path;

    if(m_data->settingsFilePath != settingspath) {
        m_data->settingsFilePath = settingspath;
        emit settingsPathChanged(settingspath);
    }
}

QString KopiAppSettings::graphicsAssetsPath() const
{
    return m_data->graphicsAssetsPath;
}

void KopiAppSettings::setGraphisAssetsPath(const QString &path)
{
    if(m_data->graphicsAssetsPath != path) {
        m_data->graphicsAssetsPath = path;
        emit graphicsAssetsPathChanged(path);
    }
}

QString KopiAppSettings::stylesPath() const
{
    return m_data->stylesPath;
}

void KopiAppSettings::setStylesPath(const QString &path)
{
    if(m_data->stylesPath != path) {
        m_data->stylesPath = path;
        emit stylesPathChanged(path);
    }
}

QJsonObject KopiAppSettings::settings() const
{
    return m_data->settings;
}

QJsonObject KopiAppSettings::settingsMac() const
{
    return m_data->settings.value("mac").toObject();
}

QJsonObject KopiAppSettings::settingsLinux() const
{
    return m_data->settings.value("linux").toObject();;
}

void KopiAppSettings::readSettings()
{
    setSettingsStatus(Loading);

    QFile settingsFile(m_data->settingsFilePath + "/kopisettings.json");
    if(settingsFile.open(QIODevice::ReadOnly)) {
        QJsonDocument jsonDocument = QJsonDocument::fromJson(settingsFile.readAll());
        m_data->settings = jsonDocument.object();

        qDebug()<<"READING SETTINGS - " << "ALL GOOD" <<settingsFile;
        readPlatformSetting();
        emit settingsChanged(m_data->settings);
        setSettingsStatus(Ready);
    } else {
        setSettingsStatus(Error);
    }
}

void KopiAppSettings::saveSettings()
{

}

void KopiAppSettings::updatePlatform()
{
#ifdef Q_OS_MACOS
    m_data->platform = MacOS;
#endif

#ifdef Q_OS_LINUX
    m_data->platform = Linux;
#endif

#ifdef Q_OS_IOS
    m_data->platform = iOS;
#endif

    emit platformChanged(m_data->platform);
}

/**
 * @brief KopiAppSettings::readPlatformSetting
 */
void KopiAppSettings::readPlatformSetting()
{
    QString graphicspath, stylespath;
    switch (m_data->platform) {
    case MacOS:
//        graphicspath = settingsMac().value("graphics_assets_path").toString();
//        stylespath = settingsMac().value("styles_path").toString();
//        break;
    case Linux:
//        graphicspath = settingsLinux().value("graphics_assets_path").toString();
//        stylespath = settingsLinux().value("styles_path").toString();
//        break;
    case iOS:
        graphicspath = ":/graphic-assets";
        stylespath = ":/stylethemes";
        break;
    }

    setGraphisAssetsPath(graphicspath);
    setStylesPath(stylespath);
}
