#include "jsonobjectlist.h"
#include <QJsonArray>

#include <QDebug>

JsonObjectList::JsonObjectList(QObject *parent)
    :QAbstractListModel (parent)
{

}

JsonObjectList::~JsonObjectList()
{

}

QHash<int, QByteArray> JsonObjectList::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Name] = "Name";
    roles[Value] = "Value";
    return roles;
}

int JsonObjectList::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return m_data.count();
}

QVariant JsonObjectList::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()
        || index.row() >= m_data.count())
        return QVariant();

    switch (role) {
    case Name:
        return m_keys.at(index.row());
    case Value:
        return m_data.value(m_keys.at(index.row()));
    default:
        return QVariant();
    }
}

QJsonValue JsonObjectList::jsonObject() const
{
    return m_jsonObject;
}

void JsonObjectList::setJsonObject(const QJsonValue &json)
{
    if(m_jsonObject != json || json.isNull()) {
        m_jsonObject = json;

        beginResetModel();
        clearData();
        if(m_jsonObject.isObject()) {
            m_data = m_jsonObject.toObject().toVariantHash();
            m_keys = m_jsonObject.toObject().keys();
        } else if(m_jsonObject.isArray()) {
            int counter = m_jsonObject.toArray().count();
            for (int i = 0; i < counter; ++i) {
                m_data.unite( m_jsonObject.toArray()[i].toObject().toVariantHash());
                m_keys.append(m_jsonObject.toArray()[i].toObject().keys());
            }
        }

        QJsonArray arrayVal;
        for (int i = 0; i < m_keys.count(); ++i) {
            if(m_jsonObject.toObject().value(m_keys[i]).isArray()) {
                arrayVal = m_jsonObject.toObject().value(m_keys[i]).toArray();
                for (int i = 0; i < arrayVal.count(); ++i) {
                    m_data.unite(arrayVal[i].toObject().toVariantHash());
                    m_keys.append(arrayVal[i].toObject().keys());
                }
            }
        }

        endResetModel();
        emit jsonObjectChanged(m_jsonObject);
    }
}

void JsonObjectList::clearData() {
    m_data.clear();
    m_keys.clear();
}
