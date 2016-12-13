#pragma once
//Project
#include "cgt/CGTShare.h"

//STL

//Qt
#include <QObject>
#include <QSharedPointer>
#include <QVariant>

struct ArrayItem {
    QString name;
    QVariant data;
};
typedef QSharedPointer<ArrayItem> SharedArrayItem;
Q_DECLARE_METATYPE(SharedArrayItem)

class ArrayValue : public QList<SharedArrayItem>
{
private:
    DataType m_type = data_null;

public:
    explicit ArrayValue(DataType type)
        : m_type(type)
    {
    }

    DataType getType() const
    {
        return m_type;
    }
    void setType(DataType type)
    {
        m_type = type;
    }
};
typedef QSharedPointer<ArrayValue> SharedArrayValue;
Q_DECLARE_METATYPE(SharedArrayValue)

struct LinkedElementInfo {
    class Element *element{};
    QString interface;
};
typedef QSharedPointer<LinkedElementInfo> SharedLinkedElementInfo;
Q_DECLARE_METATYPE(SharedLinkedElementInfo)

struct ValueFont { //-V802
    QString name;
    int size{};
    int color{};
    uchar style{};
    uchar charset{};
};
typedef QSharedPointer<ValueFont> SharedValueFont;
Q_DECLARE_METATYPE(SharedValueFont)
