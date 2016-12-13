#pragma once

//Project
#include "scenemodel/scenemodel.h"

//STL

//Qt

class EmulateCgt : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(EmulateCgt)

public:
    static void setSceneModel(SceneModel *model);
    static TCodeGenTools *getCgt();
};
