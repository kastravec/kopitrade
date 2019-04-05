#include "iexcloudglobals.h"

#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QStandardPaths>
#include <QJsonDocument>

IEXCloudGlobals *IEXCloudGlobals::m_instance = nullptr;
IEXCloudGlobals *IEXCloudGlobals::instance()
{
    if(!m_instance)
        m_instance = new IEXCloudGlobals;

    return m_instance;
}

IEXCloudGlobals::IEXCloudGlobals(QObject *parent)
    :QObject(parent)
{

}

void IEXCloudGlobals::setGlobalApiHost(const QString &host)
{
    if(m_globalApiHost != host) {
        m_globalApiHost = host;
        emit globalApiHostChanged(host);
    }
}

void IEXCloudGlobals::setGlobalEnvironment(int environment)
{
    if(m_globalEnvironment != environment) {
        m_globalEnvironment = environment;
        emit globalEnvironmentChanged(environment);
    }
}

void IEXCloudGlobals::setGlobalToken(const QString &token)
{
    if(m_globalToken != token) {
        m_globalToken = token;
        emit globalTokenChanged(token);
    }
}

void IEXCloudGlobals::readLocalIEXConfig()
{
    QDir pwdDir(QStandardPaths::standardLocations(QStandardPaths::HomeLocation)[0]);
    if(pwdDir.exists("kopi-iexcloud.config")) {
        QFile iexfile(pwdDir.path() + "/kopi-iexcloud.config");
        if(iexfile.open(QIODevice::ReadOnly)) {
            QJsonDocument jsdoc = QJsonDocument::fromJson(iexfile.readAll());
            setConfigData(jsdoc.object());
        }

        iexfile.close();
        updateGlobalVariables();
    }
}

void IEXCloudGlobals::storeIEXConfigLocally()
{
    QDir pwdDir(QStandardPaths::standardLocations(QStandardPaths::HomeLocation)[0]);
    QFile iexfile(pwdDir.path() + "/kopi-iexcloud.config");
    if(iexfile.open(QIODevice::WriteOnly)) {
        QJsonDocument jsdoc(m_iexCloudData);
        QTextStream datastream(&iexfile);
        datastream << jsdoc.toJson();
    }
}

void IEXCloudGlobals::updateGlobalVariables()
{
    switch (environment()) {
    case IEXCloudGlobals::Sandbox:
        setGlobalApiHost(apiSandboxHost());
        setGlobalToken(sandboxToken());
        break;
    case IEXCloudGlobals::Live:
        setGlobalApiHost(apiHost());
        setGlobalToken(publicToken());
        break;
    case IEXCloudGlobals::Unknown:
    default:
        setGlobalApiHost("");
        setGlobalToken("");
        break;
    }
}

IEXCloudGlobals::~IEXCloudGlobals()
{
}

int IEXCloudGlobals::environment() const
{
    return m_iexCloudData.value(IEXCloudGlobalVariables::EnvironmentType).toInt();
}

void IEXCloudGlobals::setEnvironment(int env)
{
    if(m_iexCloudData.value(IEXCloudGlobalVariables::EnvironmentType).toString() != env) {
        m_iexCloudData.insert(IEXCloudGlobalVariables::EnvironmentType, env);
        updateGlobalVariables();
        emit environmentChanged(env);
    }
}

QString IEXCloudGlobals::publicToken() const
{
    return m_iexCloudData.value(IEXCloudGlobalVariables::PublicToken).toString();
}

void IEXCloudGlobals::setPublicToken(const QString &token)
{
    if (m_iexCloudData.value(IEXCloudGlobalVariables::PublicToken).toString() != token) {
        m_iexCloudData.insert(IEXCloudGlobalVariables::PublicToken, token);
        emit publicTokenChanged(token);
    }
}

QString IEXCloudGlobals::privateToken() const
{
    return m_iexCloudData.value(IEXCloudGlobalVariables::PrivateToken).toString();
}

void IEXCloudGlobals::setPrivateToken(const QString &token)
{
    if(m_iexCloudData.value(IEXCloudGlobalVariables::PrivateToken).toString() != token) {
        m_iexCloudData.insert(IEXCloudGlobalVariables::PrivateToken, token);
        emit privateTokenChanged(token);
    }
}

QString IEXCloudGlobals::apiHost() const
{
    return m_iexCloudData.value(IEXCloudGlobalVariables::APIHostLive).toString();
}

void IEXCloudGlobals::setApiHost(const QString &host)
{
    if(m_iexCloudData.value(IEXCloudGlobalVariables::APIHostLive).toString() != host) {
        m_iexCloudData.insert(IEXCloudGlobalVariables::APIHostLive, host);
        emit apiHostChanged(host);
    }
}

QString IEXCloudGlobals::apiSandboxHost() const
{
    return m_iexCloudData.value(IEXCloudGlobalVariables::APIHostSandbox).toString();
}

void IEXCloudGlobals::setApiSandboxHost(const QString &sandbox)
{
    if(m_iexCloudData.value(IEXCloudGlobalVariables::APIHostSandbox).toString() != sandbox) {
        m_iexCloudData.insert(IEXCloudGlobalVariables::APIHostSandbox, sandbox);
        emit apiSandboxHostChanged(sandbox);
    }
}

QString IEXCloudGlobals::sandboxToken() const
{
    return m_iexCloudData.value(IEXCloudGlobalVariables::SandboxToken).toString();
}

void IEXCloudGlobals::setSandboxToken(const QString &token)
{
    if(m_iexCloudData.value(IEXCloudGlobalVariables::SandboxToken).toString() != token) {
        m_iexCloudData.insert(IEXCloudGlobalVariables::SandboxToken, token);
        emit sandboxTokenChanged(token);
    }
}

QString IEXCloudGlobals::apiVersion() const
{
    return m_iexCloudData.value(IEXCloudGlobalVariables::APILiveVersion).toString();
}

void IEXCloudGlobals::setApiVersion(const QString &version)
{
    if(m_iexCloudData.value(IEXCloudGlobalVariables::APILiveVersion).toString() != version) {
        m_iexCloudData.insert(IEXCloudGlobalVariables::APILiveVersion, version);
        emit apiVersionChanged(version);
    }
}

QJsonObject IEXCloudGlobals::configData() const
{
    return m_iexCloudData;
}

void IEXCloudGlobals::setConfigData(const QJsonObject &json)
{
    if(m_iexCloudData != json) {
        m_iexCloudData = json;
        emit configDataChanged(m_iexCloudData);
        updateGlobalVariables();
    }
}

QString IEXCloudGlobals::globalApiHost() const
{
    return m_globalApiHost + "/" + apiVersion();
}

int IEXCloudGlobals::globalEnvironment() const
{
    return m_globalEnvironment;
}

QString IEXCloudGlobals::globalToken() const
{
    return m_globalToken;
}

QByteArray IEXCloudGlobalVariables::EnvironmentType = "Environment";
QByteArray IEXCloudGlobalVariables::APIHostLive = "APIHostLive";
QByteArray IEXCloudGlobalVariables::APIHostSandbox = "APIHostSandbox";
QByteArray IEXCloudGlobalVariables::APILiveVersion = "APILiveVersion";
QByteArray IEXCloudGlobalVariables::PublicToken = "PublicToken";
QByteArray IEXCloudGlobalVariables::PrivateToken = "PrivateToken";
QByteArray IEXCloudGlobalVariables::SandboxToken = "SandboxToken";
