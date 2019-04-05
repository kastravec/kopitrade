#ifndef KOPIAPPSETTINGS_H
#define KOPIAPPSETTINGS_H

#include <QObject>
#include <QJsonObject>

class KopiAppSettings : public QObject
{
    Q_OBJECT
public:

    enum SettingStatus {
        Ready = 22,
        Error,
        Loading,
        Unkown
    };

    enum Platform {
        MacOS = 11,
        Windows,
        WinRT,
        Linux,
        Android,
        iOS,
        Undefined = -1
    };

    Q_ENUM(SettingStatus)

    Q_PROPERTY(int platform READ platform NOTIFY platformChanged)
    Q_PROPERTY(int settingsStatus READ settingsStatus NOTIFY settingsStatusChanged)
    Q_PROPERTY(QString settingsPath READ settingsPath WRITE setSettingsPath NOTIFY settingsPathChanged)
    Q_PROPERTY(QString graphicsAssetsPath READ graphicsAssetsPath WRITE setGraphisAssetsPath NOTIFY graphicsAssetsPathChanged)
    Q_PROPERTY(QString stylesPath READ stylesPath WRITE setStylesPath NOTIFY stylesPathChanged)
    Q_PROPERTY(QJsonObject settings READ settings NOTIFY settingsChanged)
    Q_PROPERTY(QJsonObject settingsMac READ settingsMac NOTIFY settingsMacChanged)
    Q_PROPERTY(QJsonObject settingsLinux READ settingsLinux NOTIFY settingsLinuxChanged)

    ~KopiAppSettings();
    static KopiAppSettings *instance();

    int platform();
    int settingsStatus() const;

    QString settingsPath() const;
    void setSettingsPath(const QString &path);

    QString graphicsAssetsPath() const;
    void setGraphisAssetsPath(const QString &path);

    QString stylesPath() const;
    void setStylesPath(const QString &path);

    QJsonObject settings() const;
    QJsonObject settingsMac() const;
    QJsonObject settingsLinux() const;

    Q_INVOKABLE void readSettings();
    Q_INVOKABLE void saveSettings();

Q_SIGNALS:
    void platformChanged(int platform);
    void settingsStatusChanged(int status);
    void settingsChanged(const QJsonObject &settings);
    void settingsMacChanged(const QJsonObject &settings);
    void settingsLinuxChanged(const QJsonObject &settings);
    void settingsPathChanged(const QString &path);
    void graphicsAssetsPathChanged(const QString &path);
    void stylesPathChanged(const QString &path);

private:
    void updatePlatform();
    void readPlatformSetting();
    explicit KopiAppSettings(QObject *parent = nullptr);
    void setSettingsStatus(int status);

    class Private;
    Private *m_data;

    static KopiAppSettings *m_instance;
};

#endif // KOPIAPPSETTINGS_H
