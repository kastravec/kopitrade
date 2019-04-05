#include "kopiuser.h"

#include "httprest.h"
#include "kopirestless.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

class KopiUser::Private {
public:
    int status;
    QJsonObject userCredentials;
    QString jwtToken;
    QJsonObject userProfile;
    QString lastErrorString;
};

KopiUser::KopiUser(QObject *parent)
    : QObject(parent)
    ,m_data(new Private)
{
    m_data->status = Unkown;
}

KopiUser::~KopiUser()
{
    delete m_data;
    m_data = nullptr;
}

int KopiUser::status() const
{
    return m_data->status;
}

QString KopiUser::jwtToken() const
{
    return m_data->jwtToken;
}

QJsonObject KopiUser::userCredentials() const
{
    return m_data->userCredentials;
}

void KopiUser::setUserCredentials(const QJsonObject &credentials)
{
    if(m_data->userCredentials != credentials ) {
        m_data->userCredentials = credentials;
        emit userCredentialsChanged(m_data->userCredentials);
    }
}

QJsonObject KopiUser::userProfile() const
{
    return m_data->userProfile;
}

void KopiUser::setUserProfile(const QJsonObject &profile)
{
    if(m_data->userProfile != profile) {
        m_data->userProfile = profile;
        emit userProfileChanged(profile);
    }
}

QString KopiUser::lastErrorString() const
{
    return m_data->lastErrorString;
}

void KopiUser::setLastErrorString(const QString &errorString)
{
    if(m_data->lastErrorString != errorString) {
        m_data->lastErrorString = errorString;
        emit lastErrorStringChanged(errorString);
    }
}

void KopiUser::registerMe(const QString &password)
{
    if(!password.isNull()) {
        setStatus(Busy);
        QString dataurl = KopiRestLess::instance()->apiHost();
        dataurl.append("/auth/local/register");
        HttpRest *rest = new HttpRest(this);
        rest->setBaseUrl(QUrl(dataurl));

        QJsonObject jsobject(m_data->userCredentials);
        jsobject.insert("password", password);
        rest->post(jsobject);

        connect(rest, &HttpRest::replyReady, this, &KopiUser::registrationHandler);
        connect(rest, &HttpRest::replyError, this, &KopiUser::registrationErrorHandler);
    }
}

void KopiUser::deleteMe()
{

}

void KopiUser::signIn(const QString &identifier, const QString &password)
{
    if(!password.isEmpty() && !identifier.isEmpty()) {
        QString dataurl = KopiRestLess::instance()->apiHost();
        dataurl.append("/auth/local");
        HttpRest *rest = new HttpRest(this);
        rest->setBaseUrl(QUrl(dataurl));

        QJsonObject datajs;
        datajs.insert("identifier", identifier);
        datajs.insert("password", password);
        rest->post(datajs);

        connect(rest, &HttpRest::replyReady, this, &KopiUser::signInHandler);
        connect(rest, &HttpRest::replyError, this, &KopiUser::signInErrorHandler);
    }
}

void KopiUser::signOut()
{

}

void KopiUser::registrationHandler(const QByteArray &replydata)
{
    qDebug()<<"REGISTRATION HANDLER: " << replydata;

    setStatus(Registered);
    sender()->deleteLater();
}

void KopiUser::registrationErrorHandler(int errorCode, const QByteArray &error)
{
    QJsonDocument jsdoc = QJsonDocument::fromJson(error);
    setLastErrorString(QString(jsdoc.object().value("message").toString()));
    setStatus(ErrorRegistering);
    sender()->deleteLater();
}

void KopiUser::signInHandler(const QByteArray &replydata)
{
    QJsonObject replyJson = QJsonDocument::fromJson(replydata).object();
    setJwtToken(replyJson.value("jwt").toString());

    QJsonObject jsobj = replyJson.value("user").toObject();
    m_data->userProfile.insert("userId", jsobj.value("id").toInt());
    m_data->userProfile.insert("username", jsobj.value("username").toString());
    m_data->userProfile.insert("email", jsobj.value("email").toString());
    m_data->userProfile.insert("blocked", jsobj.value("blocked"));
    m_data->userProfile.insert("confirmed", jsobj.value("confirmed"));
    m_data->userProfile.insert("role", jsobj.value("role").toObject().value("name").toString());

    if (m_data-> userProfile.value("userId").toInt() > -1)
        setStatus(SignedIn);
    else
        setStatus(ErrorSignIn);

    sender()->deleteLater();
}

void KopiUser::signInErrorHandler(int errorCode, const QByteArray &error)
{
    QJsonDocument jsdoc = QJsonDocument::fromJson(error);
    setLastErrorString(QString(jsdoc.object().value("message").toString()));
    setStatus(ErrorSignIn);
    sender()->deleteLater();
}

void KopiUser::signOutHandler(const QByteArray &replydata)
{

}

void KopiUser::setStatus(int st)
{
    if(m_data->status != st) {
        m_data->status = st;
        emit statusChanged(st);
    }
}

void KopiUser::setJwtToken(const QString &jwt)
{
    if(m_data->jwtToken != jwt) {
        m_data->jwtToken = jwt;
        emit jwtTokenChanged(jwt);
    }
}
