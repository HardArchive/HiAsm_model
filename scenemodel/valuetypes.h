#pragma once
//Project
#include "cgt/CGTShare.h"
#include "types.h"

//STL

//Qt
#include <QObject>
#include <QVariant>
#include <QSharedPointer>
#include <QList>

struct LinkedElementInfo {
    qintptr id{};
    QString interface;
};
typedef LinkedElementInfo *PLinkedElementInfo;
Q_DECLARE_METATYPE(PLinkedElementInfo)

struct ValueFont { //-V802
    QString name;
    uint size{};
    uchar style{};
    uint color{};
    uchar charset{};
};
typedef ValueFont *PValueFont;
Q_DECLARE_METATYPE(PValueFont)
