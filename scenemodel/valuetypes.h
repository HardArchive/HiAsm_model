#pragma once
//Project

//STL

//Qt
#include <QObject>
#include <QSharedPointer>

class Value;
typedef QSharedPointer<Value> SharedValue;
Q_DECLARE_METATYPE(SharedValue)

typedef QVector<SharedValue> Values;
Q_DECLARE_METATYPE(Values)

struct LinkedElementInfo {
    qint32 id{};
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
