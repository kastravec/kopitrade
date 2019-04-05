#ifndef JSONOBJECTLIST_H
#define JSONOBJECTLIST_H

#include <QAbstractListModel>
#include <QJsonObject>

class JsonObjectList : public QAbstractListModel
{
    Q_OBJECT
public:
    enum JsonObjectListDataRole {
        Name = Qt::UserRole + 1,
        Value
    };

    Q_PROPERTY(QJsonValue jsonObject READ jsonObject WRITE setJsonObject NOTIFY jsonObjectChanged)

    explicit JsonObjectList(QObject *parent = nullptr);
    ~JsonObjectList();

    QHash<int, QByteArray> roleNames() const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    QJsonValue jsonObject() const;
    void setJsonObject(const QJsonValue &json);

    Q_INVOKABLE void clearData();

Q_SIGNALS:
    void jsonObjectChanged(const QJsonValue &json);

private:
    QJsonValue m_jsonObject;
    QVariantHash m_data;
    QStringList m_keys;
};

#endif // JSONOBJECTLIST_H
