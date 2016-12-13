// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "globalcgt.h"

TBuildProcessRec *GlobalCgt::m_bpr = nullptr;

void GlobalCgt::setBPR(TBuildProcessRec &bpr)
{
    m_bpr = &bpr;
}

PCodeGenTools GlobalCgt::getCgt()
{
    return m_bpr->cgt;
}
