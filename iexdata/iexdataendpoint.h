#ifndef IEXDATAENDPOINT_H
#define IEXDATAENDPOINT_H

#include <QObject>
#include <QJsonValue>
#include <QUrl>

#include "iexcloudglobals.h"

class IEXDataEndpoint : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(int type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(QJsonValue jsonDataReceived READ jsonDataReceived NOTIFY jsonDataReceivedChanged)
    Q_PROPERTY(QUrl apiURL READ apiURL NOTIFY apiURLChanged)

    explicit IEXDataEndpoint(QObject *parent = nullptr, int type = IEXCloudGlobals::Stock);
    ~IEXDataEndpoint();

    int type() const;
    void setType(int t);

    QJsonValue jsonDataReceived() const;
    QUrl apiURL() const;

    Q_INVOKABLE void fetchData(const QString &options = QString());
    Q_INVOKABLE bool ready() const;

Q_SIGNALS:
    void typeChanged(int type);
    void jsonDataReceivedChanged(const QJsonValue &json);
    void errorDataReceived(int errorCode, const QByteArray &json);
    void apiURLChanged(const QUrl &url);

private Q_SLOTS:
    void iexDataDataReply(const QByteArray &datareply);
    void iexDataRequestError(int errorCode, const QByteArray &error);

private:
    void updateApiURL();
    void setApiURL(const QUrl &url);

    class Private;
    Private *m_data;
};

#endif // IEXDATAENDPOINT_H
