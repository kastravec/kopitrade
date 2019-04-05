#ifndef KOPIUSER_H
#define KOPIUSER_H

#include <QObject>
#include <QJsonObject>

class KopiUser : public QObject
{
    Q_OBJECT
public:

    enum Status {
        SignedIn = 11,
        Registered,
        NotSignedIn,
        Busy,
        ErrorSignIn,
        ErrorSignOut,
        ErrorRegistering,
        Unkown = -1
    };

    Q_ENUM(Status)
    Q_PROPERTY(int status READ status NOTIFY statusChanged)
    Q_PROPERTY(QString jwtToken READ jwtToken NOTIFY jwtTokenChanged)
    Q_PROPERTY(QJsonObject userCredentials READ userCredentials WRITE setUserCredentials NOTIFY userCredentialsChanged)
    Q_PROPERTY(QJsonObject userProfile READ userProfile WRITE setUserProfile NOTIFY userProfileChanged)
    Q_PROPERTY(QString lastErrorString READ lastErrorString WRITE setLastErrorString NOTIFY lastErrorStringChanged)

    explicit KopiUser(QObject *parent = nullptr);
    ~KopiUser();

    int status() const;
    QString jwtToken() const;

    QJsonObject userCredentials() const;
    void setUserCredentials(const QJsonObject &credentials);

    QJsonObject userProfile() const;
    void setUserProfile(const QJsonObject &profile);

    QString lastErrorString() const;
    void setLastErrorString(const QString &errorString);

    Q_INVOKABLE void registerMe(const QString &password);
    Q_INVOKABLE void deleteMe();
    Q_INVOKABLE void signIn(const QString &identifier, const QString &password);
    Q_INVOKABLE void signOut();

Q_SIGNALS:
    void userCredentialsChanged(const QJsonObject &credentials);
    void statusChanged(int status);
    void jwtTokenChanged(const QString &jwt);
    void userProfileChanged(const QJsonObject &profile);
    void lastErrorStringChanged(const QString &lastErrorStringChanged);

private Q_SLOTS:
    void registrationHandler(const QByteArray &replydata);
    void registrationErrorHandler(int errorCode, const QByteArray &error);
    void signInHandler(const QByteArray &replydata);
    void signInErrorHandler(int errorCode, const QByteArray &error);
    void signOutHandler(const QByteArray &replydata);

private:
    void setStatus(int st);
    void setJwtToken(const QString &jwt);

    class Private;
    Private *m_data;
};

#endif // KOPIUSER_H
