#pragma once
//Project
#include "cgt/CGTShare.h"

//STL

//Qt
#include <QObject>
#include <QVariant>
#include <QSharedPointer>
#include <QList>

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
typedef ValueFont *PValueFont;
Q_DECLARE_METATYPE(PValueFont)
