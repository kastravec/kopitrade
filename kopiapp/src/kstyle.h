#ifndef KSTYLE_H
#define KSTYLE_H

#include <QObject>
#include <QJsonObject>

class KStyle : public QObject
{
    Q_OBJECT
public:

    enum StyleTheme {
        Default_Light = 22,
        Default_Dark,
        Default_System,
        Undefined = -1
    };

    enum StyleStatus {
        Ready = 121,
        Loading,
        Error,
        Unknown = -1
    };

    Q_ENUM(StyleTheme)
    Q_ENUM(StyleStatus)

    Q_PROPERTY(int styleStatus READ styleStatus NOTIFY styleStatusChanged)
    Q_PROPERTY(bool kspecsEnabled READ kspecsEnabled NOTIFY kspecsEnabledChanged)
    Q_PROPERTY(QString theme READ theme WRITE setTheme NOTIFY themeChanged)
    Q_PROPERTY(QJsonObject styleDefinition READ styleDefinition WRITE setStyleDefinition NOTIFY styleDefinitionChanged)
    Q_PROPERTY(QStringList availableThemes READ availableThemes NOTIFY availableThemesChanged)

    static KStyle *instance();
    ~KStyle();

    int styleStatus() const;
    bool kspecsEnabled() const;

    QString theme() const;
    void setTheme(const QString &theme);

    QJsonObject styleDefinition() const;
    void setStyleDefinition(const QJsonObject json);

    QStringList availableThemes() const;

    Q_INVOKABLE void setDefaultTheme(int theme);
    Q_INVOKABLE void init(const QString &defaultTheme = QString());

Q_SIGNALS:
    void styleStatusChanged(int status);
    void kspecsEnabledChanged(bool enabled);
    void themeChanged(const QString &theme);
    void styleDefinitionChanged(const QJsonObject &json);
    void availableThemesChanged(const QStringList &themes);

private Q_SLOTS:
    void themeFileChanged(const QString &themeFile);

private:
    explicit KStyle(QObject *parent = nullptr);
    void initTheme();
    void checkAvailableThemes();
    void setStatus(int st);

    class Private;
    Private *m_data;

    static KStyle *m_instance;
};

#endif // KSTYLE_H
