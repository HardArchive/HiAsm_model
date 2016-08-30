#pragma once
//Project

//STL

//Qt
#include <QObject>
#include <QSharedPointer>

struct LinkedElementInfo {
    qint32 id{};
    QString interface;
};
typedef QSharedPointer<LinkedElementInfo> SharedLinkedElementInfo;
Q_DECLARE_METATYPE(SharedLinkedElementInfo)

struct ValueFont { //-V802
    QString name;
    uint size{};
    uchar style{};
    uint color{};
    uchar charset{};
};
typedef QSharedPointer<ValueFont> SharedValueFont;
Q_DECLARE_METATYPE(SharedValueFont)
