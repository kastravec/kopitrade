#include "kstyle.h"

#include "kopiappsettings.h"

#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QFileSystemWatcher>
#include <QDebug>

class KStyle::Private
{
public:
    int styleStatus;
    QString styleTheme;
    QJsonObject styleDefinition;
    QStringList availableThemes;
    QFileSystemWatcher *themeFileWatcher;
};

KStyle *KStyle::m_instance = nullptr;
KStyle *KStyle::instance()
{
    if(m_instance == nullptr)
        m_instance = new KStyle;

    return m_instance;
}

KStyle::KStyle(QObject *parent)
    :QObject(parent)
    ,m_data(new Private)
{
    setStatus(Unknown);
}

KStyle::~KStyle()
{
    delete m_data;
    m_data = nullptr;
}

void KStyle::checkAvailableThemes()
{
    QString styleFilePath = KopiAppSettings::instance()->stylesPath();
    if(!styleFilePath.isEmpty()) {
        m_data->availableThemes.clear();

        QDir dir(styleFilePath);
        QStringList filters;
        filters<<"*.json";
        QFileInfoList availableThemeFiles = dir.entryInfoList(filters, QDir::Files, QDir::NoSort);

        for (int i = 0; i < availableThemeFiles.count(); ++i)
            m_data->availableThemes.append(availableThemeFiles.at(i).fileName());

        qDebug()<<"CHECKING ALL AVAILABLE STYLES ARE IN PLACE!" <<styleFilePath <<m_data->availableThemes;
        emit availableThemesChanged(m_data->availableThemes);
    }
}

void KStyle::setStatus(int st)
{
    if(m_data->styleStatus != st) {
        m_data->styleStatus = st;
        emit styleStatusChanged(st);
    }
}

int KStyle::styleStatus() const
{
    return m_data->styleStatus;
}

bool KStyle::kspecsEnabled() const
{
    return m_data->styleDefinition.value("kspecs").toObject().value("enabled").toBool();
}

QString KStyle::theme() const
{
    return m_data->styleTheme;
}

void KStyle::setTheme(const QString &theme)
{
    if(!theme.isNull()
            && m_data->styleTheme != theme
            && m_data->availableThemes.contains(theme)) {
        m_data->styleTheme = theme;
        emit themeChanged(theme);
        initTheme();
    }
}

QJsonObject KStyle::styleDefinition() const
{
    return m_data->styleDefinition;
}

void KStyle::setStyleDefinition(const QJsonObject json)
{
    m_data->styleDefinition = json;
    emit styleDefinitionChanged(json);
    emit kspecsEnabledChanged(kspecsEnabled());
}

QStringList KStyle::availableThemes() const
{
    return m_data->availableThemes;
}

void KStyle::setDefaultTheme(int theme)
{

}

void KStyle::init(const QString &defaultTheme)
{
    if(KopiAppSettings::instance()->settingsStatus() == KopiAppSettings::Ready) {
        setStatus(Loading);
        checkAvailableThemes();

        if(m_data->availableThemes.count() <= 0) {
            setStatus(Error);
            return;
        }

        //setting a filewatcher on the theme files
        QStringList paths;
        paths<<KopiAppSettings::instance()->stylesPath();
        m_data->themeFileWatcher = new QFileSystemWatcher(this);
        bool added = m_data->themeFileWatcher->addPath(KopiAppSettings::instance()->stylesPath());
//        qDebug() <<"INIT T: " << m_data->themeFileWatcher->files() << added;
        connect(m_data->themeFileWatcher, &QFileSystemWatcher::fileChanged,
                this, &KStyle::themeFileChanged);

        setTheme(defaultTheme);
    } else {
        setStatus(Error);
    }
}

void KStyle::themeFileChanged(const QString &themeFile)
{
    QFileInfo fileInfo(themeFile);
    if(theme() == fileInfo.fileName()) {
        initTheme();
    }
}

/**
 *
 * @brief KStyle::initTheme
 * @internal internal function called to initialize the set theme
 */
void KStyle::initTheme()
{
    setStatus(Loading);

    QFile themeFile(KopiAppSettings::instance()->stylesPath() + "/" + m_data->styleTheme);
    if(themeFile.open(QIODevice::ReadOnly)) {
        QByteArray filecontent = themeFile.readAll();
        QJsonDocument themeDocument = QJsonDocument::fromJson(filecontent);
        setStyleDefinition(themeDocument.object());
        setStatus(Ready);

        m_data->themeFileWatcher->addPath(themeFile.fileName());
        qDebug() <<"INIT THEME - ALL GOOD: " << themeFile.fileName();
        return;
    }
    setStatus(Error);
}
