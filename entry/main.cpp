//Project
#include "cgt/cgt.h"
#include "cgt/emulatecgt.h"
#include "cgt/proxycgt.h"
#include "logger.h"
#include "package/packagemanager.h"
#include "scenemodel/element.h"
#include "scenemodel/scenemodel.h"

//NATIVE
#include <windows.h>

//STL

//Qt
#include <QCoreApplication>
#include <QDebug>
#include <QLibrary>

//Дефайны
#define DLLEXPORT extern "C" __cdecl
#define PRINT_FUNC_INFO qInfo("Call: %s", Q_FUNC_INFO);
#define PRINT_RESULT(X) qInfo().noquote() << "Return:" << X;

//Служебные переменные
static QLibrary codegen;
static SceneModel *sceneModel1 = nullptr;
static SceneModel *sceneModel2 = nullptr;

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved)
{
    Q_UNUSED(lpReserved)

    switch (reason) {
    case DLL_PROCESS_ATTACH: {
        //ru Инициализация логгера
        logger::initialize();

        qInfo() << "CODEGEN_PROCESS_ATTACH";

        //ru Вычисляем путь к оригинальному кодогенератору относительно текущего модуля (hModule)
        const uint max_path = 2048;
        char tmpCurrentModulePath[max_path];
        GetModuleFileNameA(hModule, tmpCurrentModulePath, max_path);
        QFileInfo currentModulePath(QString::fromLocal8Bit(tmpCurrentModulePath));
        const QString nameOriginal = "CodeGen_original.dll";
        QString pathOriginal = currentModulePath.absolutePath() + QDir::separator() + nameOriginal;
        pathOriginal = QDir::toNativeSeparators(pathOriginal);

        //ru Загружаем оригинальную DLL в память
        if (!QFile::exists(pathOriginal)) {
            qCritical("%s library not found!", qPrintable(nameOriginal));
            exit(0);
        }
        codegen.setFileName(pathOriginal);
        if (codegen.load())
            qInfo("%s library successfully loaded.", qUtf8Printable(nameOriginal));
        else
            qCritical("%s library is not loaded.", qUtf8Printable(nameOriginal));

        //ru Определение прототипов функций проксируемого кодогенератора
        buildPrepareProcLib = reinterpret_cast<TBuildPrepareProc>(codegen.resolve("buildPrepareProc"));
        buildProcessProcLib = reinterpret_cast<TBuildProcessProc>(codegen.resolve("buildProcessProc"));
        checkVersionProcLib = reinterpret_cast<TCheckVersionProc>(codegen.resolve("CheckVersionProc"));
        break;
    }

    case DLL_PROCESS_DETACH: {
        qInfo() << "CODEGEN_PROCESS_DETACH";

        delete sceneModel1;
        delete sceneModel2;
        codegen.unload();
        break;
    }
    }

    return TRUE;
}

//Экспортируемые функции
DLLEXPORT int buildPrepareProc(void *params)
{
    PRINT_FUNC_INFO

    Q_UNUSED(params)
    return buildPrepareProcLib(params);
}

DLLEXPORT int buildProcessProc(TBuildProcessRec &params)
{
    PRINT_FUNC_INFO

#ifdef MODEL
    PackageManager *manager = new PackageManager();
    sceneModel1 = new SceneModel(manager);
    sceneModel1->initFromCgt(params.cgt, params.sdk);
    sceneModel1->saveModel("test.json");

    sceneModel2 = new SceneModel(manager);
    sceneModel2->loadModel("test.json");

    EmulateCgt::setSceneModel(sceneModel2);
    params.cgt = EmulateCgt::getCgt();
#endif

#ifdef PROXY_MODEL
    ProxyCgt::setProxiedCgt(EmulateCgt::getCgt());
    params.cgt = ProxyCgt::getCgt();
#endif

#ifdef PROXY_ORIGINAL
    ProxyCgt::setProxiedCgt(params.cgt);
    params.cgt = ProxyCgt::getCgt();
#endif

    int res = buildProcessProcLib(params);
    PRINT_RESULT(CgResultMap[res]);

    return res;
}

DLLEXPORT int CheckVersionProc(const THiAsmVersion &params)
{
    PRINT_FUNC_INFO
    qInfo().noquote() << QString("Arg1: %1.%2.%3").arg(params.major).arg(params.minor).arg(params.build);
    int res = checkVersionProcLib(params);
    PRINT_RESULT(CgResultMap[res]);
    return res;
}
