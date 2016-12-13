#pragma once

#include "cgt/CGTShare.h"

#include <QObject>

class GlobalCgt
{
    Q_DISABLE_COPY(GlobalCgt)
    GlobalCgt() Q_DECL_EQ_DELETE;

private:
    static TBuildProcessRec *m_bpr;

public:
    static void setBPR(TBuildProcessRec &bpr);
    static PCodeGenTools getCgt();
};
