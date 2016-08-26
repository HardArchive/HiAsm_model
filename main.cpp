//NATIVE
#include <windows.h>

//STL

//Qt
#include <QCoreApplication>
#include <QDebug>
#include <QLibrary>

#define DLLEXPORT extern "C" __declspec(dllexport)
#define PRINT_FUNC_INFO qInfo("Call: %s", Q_FUNC_INFO);
#define PRINT_RESULT(X) qInfo("Return: %s", X);

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved)
{
    Q_UNUSED(lpReserved)

    switch (reason) {
    case DLL_PROCESS_ATTACH: {
        qInfo() << "CODEGEN_PROCESS_ATTACH";

        break;
    }

    case DLL_PROCESS_DETACH: {
        qInfo() << "CODEGEN_PROCESS_DETACH";

        break;
    }
    }

    return TRUE;
}

//Экспортируемые функции
DLLEXPORT int buildPrepareProc(void *params)
{
    PRINT_FUNC_INFO
    return 0;
}

DLLEXPORT int buildProcessProc(void *params)
{
    PRINT_FUNC_INFO
    return 0;
}

struct THiAsmVersion {
    short int major{};
    short int minor{};
    short int build{};
};

DLLEXPORT int CheckVersionProc(const THiAsmVersion &params)
{
    PRINT_FUNC_INFO
    qInfo() << QString("Arg1: %1.%2.%3").arg(params.major).arg(params.minor).arg(params.build);
    //int res = checkVersionProcLib(params);
    //PRINT_RESULT(CgResultMap[res]);
    //return res;
    return 0;
}
