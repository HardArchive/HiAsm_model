#pragma once

//Project
#include "CGTShare.h"

//STL

//Qt

class ProxyCgt : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(ProxyCgt)

public:
    static void setProxiedCgt(TCodeGenTools *cgt);
    static TCodeGenTools *getCgt();
};
