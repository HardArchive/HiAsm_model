//Project
#include "proxycgt.h"

//STL

//Qt
#include <QDebug>
#include <QFlags>

namespace ProxyCgt
{
    //Дефайны
#define EXPORT __stdcall
#define PRINT_FUNC_INFO qInfo("  Call: %s", Q_FUNC_INFO);
#define PRINT_RESULT(X) qInfo().noquote() << "  Return:" << X;

#define id(X) QString("id(%1)").arg(X)
#define str(X) QString("\"%1\"").arg(QString::fromLocal8Bit(X))
#define p(X) QString("p(%1)").arg(X)

    //Для хранения указателя на массив указателей на callback функции
    static PCodeGenTools m_cgt = nullptr;

    //Служебные функции
    void printArgs(const std::initializer_list<QVariant> &args)
    {
        uint numArg = 1;
        for (const QVariant &v : args) {
            qInfo().noquote() << QString("  Arg%1: %2").arg(numArg).arg(v.toString());
            ++numArg;
        }
    }
    void printParamArgs(CgtParams index, const QVariant &value)
    {
        qInfo("  Arg1: %s", qUtf8Printable(CgtParamsMap[index])); //-V108
        if (value.type() == QVariant::String) {
            qInfo("  Arg2: \"%s\"", qUtf8Printable(value.toString()));
        } else {
            qInfo("  Arg2: %s", qUtf8Printable(value.toString()));
        }
    }


    //~~~~~~~~~~~~~~~~~ Проксированные функции ~~~~~~~~~~~~~~~~~~~

    EXPORT int sdkGetCount(qintptr id_sdk)
    {
        PRINT_FUNC_INFO
        int res = m_cgt->sdkGetCount(id_sdk);
        printArgs({id(id_sdk)});
        PRINT_RESULT(res)

        return res;
    }
    EXPORT qintptr sdkGetElement(qintptr id_sdk, int index)
    {
        PRINT_FUNC_INFO
        qintptr res = m_cgt->sdkGetElement(id_sdk, index);
        printArgs({id(id_sdk), index});
        PRINT_RESULT(id(res))

        return res;
    }
    EXPORT qintptr sdkGetElementName(qintptr id_sdk, char *name)
    {
        PRINT_FUNC_INFO
        qintptr res = m_cgt->sdkGetElementName(id_sdk, name);
        printArgs({id(id_sdk), str(name)});
        PRINT_RESULT(id(res))

        return res;
    }
    EXPORT ElementFlags elGetFlag(qintptr id_element)
    {
        PRINT_FUNC_INFO
        ElementFlags res = m_cgt->elGetFlag(id_element);
        printArgs({id(id_element)});
        PRINT_RESULT(ElementFlgs(res))

        return res;
    }
    EXPORT int elGetPropCount(qintptr id_element)
    {
        PRINT_FUNC_INFO
        int res = m_cgt->elGetPropCount(id_element);
        printArgs({id(id_element)});
        PRINT_RESULT(res)

        return res;
    }
    EXPORT qintptr elGetProperty(qintptr id_element, int index)
    {
        PRINT_FUNC_INFO
        qintptr res = m_cgt->elGetProperty(id_element, index);
        printArgs({id(id_element), index});
        PRINT_RESULT(id(res))

        return res;
    }
    EXPORT bool elIsDefProp(qintptr id_element, int index)
    {
        PRINT_FUNC_INFO
        bool res = m_cgt->elIsDefProp(id_element, index);
        printArgs({id(id_element), index});
        PRINT_RESULT(res)

        return res;
    }
    EXPORT qintptr elSetCodeName(qintptr id_element, const char *name)
    {
        PRINT_FUNC_INFO
        qintptr res = m_cgt->elSetCodeName(id_element, name);
        printArgs({id(id_element), str(name)});
        PRINT_RESULT(id(res))

        return res;
    }
    EXPORT const char *elGetCodeName(qintptr id_element)
    {
        PRINT_FUNC_INFO
        const char *res = m_cgt->elGetCodeName(id_element);
        printArgs({id(id_element)});
        PRINT_RESULT(str(res))

        return res;
    }
    EXPORT const char *elGetClassName(qintptr id_element)
    {
        PRINT_FUNC_INFO
        const char *res = m_cgt->elGetClassName(id_element);
        printArgs({id(id_element)});
        PRINT_RESULT(str(res))

        return res;
    }
    EXPORT const char *elGetInfSub(qintptr id_element)
    {
        PRINT_FUNC_INFO
        const char *res = m_cgt->elGetInfSub(id_element);
        printArgs({id(id_element)});
        PRINT_RESULT(str(res))

        return res;
    }
    EXPORT int elGetPtCount(qintptr id_element)
    {
        PRINT_FUNC_INFO
        int res = m_cgt->elGetPtCount(id_element);
        printArgs({id(id_element)});
        PRINT_RESULT(res)

        return res;
    }
    EXPORT qintptr elGetPt(qintptr id_element, int index)
    {
        PRINT_FUNC_INFO
        qintptr res = m_cgt->elGetPt(id_element, index);
        printArgs({id(id_element), index});
        PRINT_RESULT(id(res))

        return res;
    }
    EXPORT qintptr elGetPtName(qintptr id_element, const char *name)
    {
        PRINT_FUNC_INFO
        qintptr res = m_cgt->elGetPtName(id_element, name);
        printArgs({id(id_element), str(name)});
        PRINT_RESULT(id(res))

        return res;
    }
    EXPORT ElementClass elGetClassIndex(qintptr id_element)
    {
        PRINT_FUNC_INFO
        ElementClass res = m_cgt->elGetClassIndex(id_element);
        printArgs({id(id_element)});
        PRINT_RESULT(ElementClassMap[res]) //-V108

        return res;
    }
    EXPORT qintptr elGetSDK(qintptr id_element)
    {
        PRINT_FUNC_INFO
        qintptr res = m_cgt->elGetSDK(id_element);
        printArgs({id(id_element)});
        PRINT_RESULT(id(res))

        return res;
    }
    EXPORT bool elLinkIs(qintptr id_element)
    {
        PRINT_FUNC_INFO
        bool res = m_cgt->elLinkIs(id_element);
        printArgs({id(id_element)});
        PRINT_RESULT(res)

        return res;
    }
    EXPORT qintptr elLinkMain(qintptr id_element)
    {
        PRINT_FUNC_INFO
        qintptr res = m_cgt->elLinkMain(id_element);
        printArgs({id(id_element)});
        PRINT_RESULT(id(res))

        return res;
    }
    EXPORT void elGetPos(qintptr id_element, int &X, int &Y)
    {
        PRINT_FUNC_INFO
        m_cgt->elGetPos(id_element, X, Y);
        printArgs({id(id_element), X, Y});
    }
    EXPORT void elGetSize(qintptr id_element, int &W, int &H)
    {
        PRINT_FUNC_INFO
        m_cgt->elGetSize(id_element, W, H);
        printArgs({id(id_element), W, H});
    }
    EXPORT int elGetEID(qintptr id_point)
    {
        PRINT_FUNC_INFO
        int res = m_cgt->elGetEID(id_point);
        printArgs({id(id_point)});
        PRINT_RESULT(res)

        return res;
    }
    EXPORT qintptr ptGetLinkPoint(qintptr id_point)
    {
        PRINT_FUNC_INFO
        qintptr res = m_cgt->ptGetLinkPoint(id_point);
        printArgs({id(id_point)});
        PRINT_RESULT(id(res))

        return res;
    }
    EXPORT qintptr ptGetRLinkPoint(qintptr id_point)
    {
        PRINT_FUNC_INFO
        qintptr res = m_cgt->ptGetRLinkPoint(id_point);
        printArgs({id(id_point)});
        PRINT_RESULT(id(res))

        return res;
    }
    EXPORT PointType ptGetType(qintptr id_point)
    {
        PRINT_FUNC_INFO
        PointType res = m_cgt->ptGetType(id_point);
        printArgs({id(id_point)});
        PRINT_RESULT(PointTypeMap[res]) //-V108

        return res;
    }
    EXPORT const char *ptGetName(qintptr id_point)
    {
        PRINT_FUNC_INFO
        const char *res = m_cgt->ptGetName(id_point);
        printArgs({id(id_point)});
        PRINT_RESULT(str(res))

        return res;
    }
    EXPORT qintptr ptGetParent(qintptr id_point)
    {
        PRINT_FUNC_INFO
        qintptr res = m_cgt->ptGetParent(id_point);
        printArgs({id(id_point)});
        PRINT_RESULT(id(res))

        return res;
    }
    EXPORT int ptGetIndex(qintptr id_point)
    {
        PRINT_FUNC_INFO
        int res = m_cgt->ptGetIndex(id_point);
        printArgs({id(id_point)});
        PRINT_RESULT(res)

        return res;
    }
    EXPORT const char *pt_dpeGetName(qintptr id_point)
    {
        PRINT_FUNC_INFO
        const char *res = m_cgt->pt_dpeGetName(id_point);
        printArgs({id(id_point)});
        PRINT_RESULT(str(res))

        return res;
    }
    EXPORT DataType propGetType(qintptr id_prop)
    {
        PRINT_FUNC_INFO
        DataType res = m_cgt->propGetType(id_prop);
        printArgs({id(id_prop)});
        PRINT_RESULT(DataTypeMap[res]) //-V108

        return res;
    }
    EXPORT const char *propGetName(qintptr id_prop)
    {
        PRINT_FUNC_INFO
        const char *res = m_cgt->propGetName(id_prop);
        printArgs({id(id_prop)});
        PRINT_RESULT(str(res))

        return res;
    }
    EXPORT qintptr propGetValue(qintptr id_prop)
    {
        PRINT_FUNC_INFO
        qintptr res = m_cgt->propGetValue(id_prop);
        printArgs({id(id_prop)});
        PRINT_RESULT(id(res))

        return res;
    }
    EXPORT uchar propToByte(qintptr id_prop)
    {
        PRINT_FUNC_INFO
        uchar res = m_cgt->propToByte(id_prop);
        printArgs({id(id_prop)});
        PRINT_RESULT(res)

        return res;
    }
    EXPORT int propToInteger(qintptr id_prop)
    {
        PRINT_FUNC_INFO
        int res = m_cgt->propToInteger(id_prop);
        printArgs({id(id_prop)});
        PRINT_RESULT(res)

        return res;
    }
    EXPORT qreal propToReal(qintptr id_prop)
    {
        PRINT_FUNC_INFO
        float res = m_cgt->propToReal(id_prop);
        printArgs({id(id_prop)});
        PRINT_RESULT(res)

        return res;
    }
    EXPORT const char *propToString(qintptr id_prop)
    {
        PRINT_FUNC_INFO
        const char *res = m_cgt->propToString(id_prop);
        printArgs({id(id_prop)});
        PRINT_RESULT(str(res))

        return res;
    }
    EXPORT int resAddFile(const char *name)
    {
        PRINT_FUNC_INFO
        int res = m_cgt->resAddFile(name);
        printArgs({str(name)});
        PRINT_RESULT(res)

        return res;
    }
    EXPORT const char *resAddIcon(qintptr id_prop)
    {
        PRINT_FUNC_INFO
        const char *res = m_cgt->resAddIcon(id_prop);
        printArgs({id(id_prop)});
        PRINT_RESULT(str(res))

        return res;
    }
    EXPORT const char *resAddStr(const char *str)
    {
        PRINT_FUNC_INFO
        const char *res = m_cgt->resAddStr(str);
        printArgs({str});
        PRINT_RESULT(str(res))

        return res;
    }
    EXPORT const char *resAddStream(qintptr id_prop)
    {
        PRINT_FUNC_INFO
        const char *res = m_cgt->resAddStream(id_prop);
        printArgs({id(id_prop)});
        PRINT_RESULT(str(res))

        return res;
    }
    EXPORT const char *resAddWave(qintptr id_prop)
    {
        PRINT_FUNC_INFO
        const char *res = m_cgt->resAddWave(id_prop);
        printArgs({id(id_prop)});
        PRINT_RESULT(str(res))

        return res;
    }
    EXPORT const char *resAddBitmap(qintptr id_prop)
    {
        PRINT_FUNC_INFO
        const char *res = m_cgt->resAddBitmap(id_prop);
        printArgs({id(id_prop)});
        PRINT_RESULT(str(res))

        return res;
    }
    EXPORT const char *resAddMenu(qintptr id_prop)
    {
        PRINT_FUNC_INFO
        const char *res = m_cgt->resAddMenu(id_prop);
        printArgs({id(id_prop)});
        PRINT_RESULT(str(res))

        return res;
    }
    EXPORT int _Debug(const char *text, int color)
    {
        PRINT_FUNC_INFO
        int res = m_cgt->_Debug(text, color);
        printArgs({str(text), color});
        PRINT_RESULT(res)

        return res;
    }
    EXPORT int GetParam(CgtParams index, void *value)
    {
        PRINT_FUNC_INFO
        if (index > 12)
            index = PARAM_DEBUG_MODE;

        int res = m_cgt->GetParam(index, value);

        switch (index) {
        case PARAM_CODE_PATH :
            printParamArgs(index, reinterpret_cast<const char *>(value));
            break;
        case PARAM_DEBUG_MODE:
            printParamArgs(index, *reinterpret_cast<const int *>(value)); //-V206
            break;
        case PARAM_DEBUG_SERVER_PORT:
            printParamArgs(index, *reinterpret_cast<const int *>(value)); //-V206
            break;
        case PARAM_DEBUG_CLIENT_PORT:
            printParamArgs(index, *reinterpret_cast<const int *>(value)); //-V206
            break;
        case PARAM_PROJECT_PATH:
            printParamArgs(index, reinterpret_cast<const char *>(value));
            break;
        case PARAM_HIASM_VERSION:
            printParamArgs(index, reinterpret_cast<const char *>(value));
            break;
        case PARAM_USER_NAME:
            printParamArgs(index, reinterpret_cast<const char *>(value));
            break;
        case PARAM_USER_MAIL:
            printParamArgs(index, reinterpret_cast<const char *>(value));
            break;
        case PARAM_PROJECT_NAME:
            printParamArgs(index, reinterpret_cast<const char *>(value));
            break;
        case PARAM_SDE_WIDTH:
            printParamArgs(index, *reinterpret_cast<const int *>(value)); //-V206
            break;
        case PARAM_SDE_HEIGHT:
            printParamArgs(index, *reinterpret_cast<const int *>(value)); //-V206
            break;
        case PARAM_COMPILER:
            printParamArgs(index, reinterpret_cast<const char *>(value));
            break;
        }

        PRINT_RESULT(res)

        return res;
    }
    EXPORT int arrCount(qintptr id_value)
    {
        PRINT_FUNC_INFO
        int res = m_cgt->arrCount(id_value);
        printArgs({id(id_value)});
        PRINT_RESULT(res)

        return res;
    }
    EXPORT DataType arrType(qintptr id_value)
    {
        PRINT_FUNC_INFO
        DataType res = m_cgt->arrType(id_value);
        printArgs({id(id_value)});
        PRINT_RESULT(DataTypeMap[res]) //-V108

        return res;
    }
    EXPORT const char *arrItemName(qintptr id_value, int index)
    {
        PRINT_FUNC_INFO
        const char *res = m_cgt->arrItemName(id_value, index);
        printArgs({id(id_value), index});
        PRINT_RESULT(str(res))

        return res;
    }
    EXPORT qintptr arrItemData(qintptr id_value, int index)
    {
        PRINT_FUNC_INFO
        const qintptr res = m_cgt->arrItemData(id_value, index);
        printArgs({id(id_value), index});
        PRINT_RESULT(id(res))

        return res;
    }
    EXPORT qintptr arrGetItem(qintptr id_value, int index)
    {
        PRINT_FUNC_INFO
        qintptr res = m_cgt->arrGetItem(id_value, index);
        printArgs({id(id_value), index});
        PRINT_RESULT(id(res))

        return res;
    }
    EXPORT int isDebug(qintptr id_element)
    {
        PRINT_FUNC_INFO
        int res = m_cgt->isDebug(id_element);
        printArgs({id(id_element)});
        PRINT_RESULT(res)

        return res;
    }
    EXPORT DataType dtType(qintptr id_value)
    {
        PRINT_FUNC_INFO
        DataType res = m_cgt->dtType(id_value);
        printArgs({id(id_value)});
        PRINT_RESULT(DataTypeMap[res]) //-V108

        return res;
    }
    EXPORT const char *dtStr(qintptr id_value)
    {
        PRINT_FUNC_INFO
        const char *res = m_cgt->dtStr(id_value);
        printArgs({id(id_value)});
        PRINT_RESULT(str(res))

        return res;
    }
    EXPORT int dtInt(qintptr id_value)
    {
        PRINT_FUNC_INFO
        int res = m_cgt->dtInt(id_value);
        printArgs({id(id_value)});
        PRINT_RESULT(res)

        return res;
    }
    EXPORT qreal dtReal(qintptr id_value)
    {
        PRINT_FUNC_INFO
        qreal res = m_cgt->dtReal(id_value);
        printArgs({id(id_value)});
        PRINT_RESULT(res)

        return res;
    }
    EXPORT const char *fntName(qintptr id_value)
    {
        PRINT_FUNC_INFO
        const char *res = m_cgt->fntName(id_value);
        printArgs({id(id_value)});
        PRINT_RESULT(res)

        return res;
    }
    EXPORT int fntSize(qintptr id_value)
    {
        PRINT_FUNC_INFO
        int res = m_cgt->fntSize(id_value);
        printArgs({id(id_value)});
        PRINT_RESULT(res)

        return res;
    }
    EXPORT uchar fntStyle(qintptr id_value)
    {
        printArgs({id(id_value)});
        PRINT_FUNC_INFO
        uchar res = m_cgt->fntStyle(id_value);
        PRINT_RESULT(res)

        return res;
    }
    EXPORT uint fntColor(qintptr id_value)
    {
        PRINT_FUNC_INFO
        int res = m_cgt->fntColor(id_value);
        printArgs({id(id_value)});
        PRINT_RESULT(res)

        return res;
    }
    EXPORT uchar fntCharSet(qintptr id_value)
    {
        PRINT_FUNC_INFO
        uchar res = m_cgt->fntCharSet(id_value);
        printArgs({id(id_value)});
        PRINT_RESULT(res)

        return res;
    }
    EXPORT qintptr elGetData(qintptr id_element)
    {
        PRINT_FUNC_INFO
        const qintptr res = m_cgt->elGetData(id_element);
        printArgs({id(id_element)});
        PRINT_RESULT(p(res))

        return res;
    }
    EXPORT void elSetData(qintptr id_element, qintptr data)
    {
        PRINT_FUNC_INFO
        m_cgt->elSetData(id_element, data);
        printArgs({id(id_element), p(data)});
    }
    EXPORT DataType ptGetDataType(qintptr id_point)
    {
        PRINT_FUNC_INFO
        DataType res = m_cgt->ptGetDataType(id_point);
        printArgs({id(id_point)});
        PRINT_RESULT(DataTypeMap[res]) //-V108

        return res;
    }
    EXPORT qintptr elGetParent(qintptr id_element)
    {
        PRINT_FUNC_INFO
        qintptr res = m_cgt->elGetParent(id_element);
        printArgs({id(id_element)});
        PRINT_RESULT(id(res))

        return res;
    }
    EXPORT int elGetPropertyListCount(qintptr id_element)
    {
        PRINT_FUNC_INFO
        int res = m_cgt->elGetPropertyListCount(id_element);
        printArgs({id(id_element)});
        PRINT_RESULT(res)

        return res;
    }
    EXPORT qintptr elGetPropertyListItem(qintptr id_element, int index)
    {
        PRINT_FUNC_INFO
        qintptr res = m_cgt->elGetPropertyListItem(id_element, index);
        printArgs({id(id_element), index});
        PRINT_RESULT(id(res))

        return res;
    }
    EXPORT const char *plGetName(qintptr id_point)
    {
        PRINT_FUNC_INFO
        const char *res = m_cgt->plGetName(id_point);
        printArgs({id(id_point)});
        PRINT_RESULT(str(res))

        return res;
    }
    EXPORT const char *plGetInfo(qintptr id_point)
    {
        PRINT_FUNC_INFO
        const char *res = m_cgt->plGetInfo(id_point);
        printArgs({id(id_point)});
        PRINT_RESULT(str(res))

        return res;
    }
    EXPORT const char *plGetGroup(qintptr id_point)
    {
        PRINT_FUNC_INFO
        const char *res = m_cgt->plGetGroup(id_point);
        printArgs({id(id_point)});
        PRINT_RESULT(str(res))

        return res;
    }
    EXPORT qintptr plGetProperty(qintptr id_point)
    {
        PRINT_FUNC_INFO
        qintptr res = m_cgt->plGetProperty(id_point);
        printArgs({id(id_point)});
        PRINT_RESULT(id(res))

        return res;
    }
    EXPORT qintptr plGetOwner(qintptr id_prop)
    {
        PRINT_FUNC_INFO
        qintptr res = m_cgt->plGetOwner(id_prop);
        printArgs({id(id_prop)});
        PRINT_RESULT(id(res))

        return res;
    }
    EXPORT const char *ptGetInfo(qintptr id_prop)
    {
        PRINT_FUNC_INFO
        const char *res = m_cgt->ptGetInfo(id_prop);
        printArgs({id(id_prop)});
        PRINT_RESULT(str(res))

        return res;
    }
    EXPORT qintptr propGetLinkedElement(qintptr id_prop, const char *propName)
    {
        PRINT_FUNC_INFO
        qintptr res = m_cgt->propGetLinkedElement(id_prop, propName);
        printArgs({id(id_prop), str(propName)});
        PRINT_RESULT(id(res))

        return res;
    }
    EXPORT int propIsTranslate(qintptr id_element, qintptr id_prop)
    {
        PRINT_FUNC_INFO
        int res = m_cgt->propIsTranslate(id_element, id_prop);
        printArgs({id(id_element), id(id_prop)});
        PRINT_RESULT(res)

        return res;
    }
    EXPORT qintptr propGetLinkedElementInfo(qintptr id_element, qintptr id_prop, char *info)
    {
        PRINT_FUNC_INFO
        qintptr res = m_cgt->propGetLinkedElementInfo(id_element, id_prop, info);
        printArgs({id(id_element), id(id_prop), str(info)});
        PRINT_RESULT(id(res))

        return 0;
    }
    EXPORT qintptr elGetSDKByIndex(qintptr id_element, int index)
    {
        PRINT_FUNC_INFO
        qintptr res = m_cgt->elGetSDKByIndex(id_element, index);
        printArgs({id(id_element), index});
        PRINT_RESULT(id(res))

        return res;
    }
    EXPORT int elGetSDKCount(qintptr id_element)
    {
        PRINT_FUNC_INFO
        int res = m_cgt->elGetSDKCount(id_element);
        printArgs({id(id_element)});
        PRINT_RESULT(res)

        return res;
    }
    EXPORT const char *elGetSDKName(qintptr id_element, int index)
    {
        PRINT_FUNC_INFO
        const char *res = m_cgt->elGetSDKName(id_element, index);
        printArgs({id(id_element), index});
        PRINT_RESULT(str(res))

        return res;
    }
    EXPORT qintptr sdkGetParent(qintptr id_sdk)
    {
        PRINT_FUNC_INFO
        qintptr res = m_cgt->sdkGetParent(id_sdk);
        printArgs({id(id_sdk)});
        PRINT_RESULT(id(res))

        return res;
    }
    EXPORT const char *elGetInterface(qintptr id_element)
    {
        PRINT_FUNC_INFO
        const char *res = m_cgt->elGetInterface(id_element);
        printArgs({id(id_element)});
        PRINT_RESULT(str(res))

        return res;
    }
    EXPORT const char *elGetInherit(qintptr id_element)
    {
        PRINT_FUNC_INFO
        const char *res = m_cgt->elGetInherit(id_element);
        printArgs({id(id_element)});
        PRINT_RESULT(str(res))

        return res;
    }
    EXPORT int resEmpty()
    {
        PRINT_FUNC_INFO
        int res = m_cgt->resEmpty();
        PRINT_RESULT(res)

        return res;
    }
    EXPORT int resSetPref(const char *pref)
    {
        PRINT_FUNC_INFO
        int res = m_cgt->resSetPref(pref);
        printArgs({str(pref)});
        PRINT_RESULT(res)

        return res;
    }
    EXPORT int _Error(int line, qintptr id_element, const char *text)
    {
        PRINT_FUNC_INFO
        int res = m_cgt->_Error(line, id_element, text);
        printArgs({line, id(id_element), str(text)});
        PRINT_RESULT(res)

        return res;
    }
    EXPORT int elGetGroup(qintptr id_element)
    {
        PRINT_FUNC_INFO
        int res = m_cgt->elGetGroup(id_element);
        printArgs({id(id_element)});
        PRINT_RESULT(res)

        return res;
    }
    EXPORT int propSaveToFile(qintptr id_prop, const char *fileName)
    {
        PRINT_FUNC_INFO
        int res = m_cgt->propSaveToFile(id_prop, fileName);
        printArgs({id(id_prop), str(fileName)});
        PRINT_RESULT(res)

        return res;
    }

    static qintptr proxyCgt[] {
        reinterpret_cast<qintptr>(sdkGetCount),
        reinterpret_cast<qintptr>(sdkGetElement),
        reinterpret_cast<qintptr>(sdkGetElementName),
        reinterpret_cast<qintptr>(elGetFlag),
        reinterpret_cast<qintptr>(elGetPropCount),
        reinterpret_cast<qintptr>(elGetProperty),
        reinterpret_cast<qintptr>(elIsDefProp),
        reinterpret_cast<qintptr>(elSetCodeName),
        reinterpret_cast<qintptr>(elGetCodeName),
        reinterpret_cast<qintptr>(elGetClassName),
        reinterpret_cast<qintptr>(elGetInfSub),
        reinterpret_cast<qintptr>(elGetPtCount),
        reinterpret_cast<qintptr>(elGetPt),
        reinterpret_cast<qintptr>(elGetPtName),
        reinterpret_cast<qintptr>(elGetClassIndex),
        reinterpret_cast<qintptr>(elGetSDK),
        reinterpret_cast<qintptr>(elLinkIs),
        reinterpret_cast<qintptr>(elLinkMain),
        reinterpret_cast<qintptr>(elGetPos),
        reinterpret_cast<qintptr>(elGetSize),
        reinterpret_cast<qintptr>(elGetEID),
        reinterpret_cast<qintptr>(ptGetLinkPoint),
        reinterpret_cast<qintptr>(ptGetRLinkPoint),
        reinterpret_cast<qintptr>(ptGetType),
        reinterpret_cast<qintptr>(ptGetName),
        reinterpret_cast<qintptr>(ptGetParent),
        reinterpret_cast<qintptr>(ptGetIndex),
        reinterpret_cast<qintptr>(pt_dpeGetName),
        reinterpret_cast<qintptr>(propGetType),
        reinterpret_cast<qintptr>(propGetName),
        reinterpret_cast<qintptr>(propGetValue),
        reinterpret_cast<qintptr>(propToByte),
        reinterpret_cast<qintptr>(propToInteger),
        reinterpret_cast<qintptr>(propToReal),
        reinterpret_cast<qintptr>(propToString),
        reinterpret_cast<qintptr>(resAddFile),
        reinterpret_cast<qintptr>(resAddIcon),
        reinterpret_cast<qintptr>(resAddStr),
        reinterpret_cast<qintptr>(resAddStream),
        reinterpret_cast<qintptr>(resAddWave),
        reinterpret_cast<qintptr>(resAddBitmap),
        reinterpret_cast<qintptr>(resAddMenu),
        reinterpret_cast<qintptr>(_Debug),
        reinterpret_cast<qintptr>(GetParam),
        reinterpret_cast<qintptr>(arrCount),
        reinterpret_cast<qintptr>(arrType),
        reinterpret_cast<qintptr>(arrItemName),
        reinterpret_cast<qintptr>(arrItemData),
        reinterpret_cast<qintptr>(arrGetItem),
        reinterpret_cast<qintptr>(isDebug),
        reinterpret_cast<qintptr>(dtType),
        reinterpret_cast<qintptr>(dtStr),
        reinterpret_cast<qintptr>(dtInt),
        reinterpret_cast<qintptr>(dtReal),
        reinterpret_cast<qintptr>(fntName),
        reinterpret_cast<qintptr>(fntSize),
        reinterpret_cast<qintptr>(fntStyle),
        reinterpret_cast<qintptr>(fntColor),
        reinterpret_cast<qintptr>(fntCharSet),
        reinterpret_cast<qintptr>(elGetData),
        reinterpret_cast<qintptr>(elSetData),
        reinterpret_cast<qintptr>(ptGetDataType),
        reinterpret_cast<qintptr>(elGetParent),
        reinterpret_cast<qintptr>(elGetPropertyListCount),
        reinterpret_cast<qintptr>(elGetPropertyListItem),
        reinterpret_cast<qintptr>(plGetName),
        reinterpret_cast<qintptr>(plGetInfo),
        reinterpret_cast<qintptr>(plGetGroup),
        reinterpret_cast<qintptr>(plGetProperty),
        reinterpret_cast<qintptr>(plGetOwner),
        reinterpret_cast<qintptr>(ptGetInfo),
        reinterpret_cast<qintptr>(propGetLinkedElement),
        reinterpret_cast<qintptr>(propIsTranslate),
        reinterpret_cast<qintptr>(propGetLinkedElementInfo),
        reinterpret_cast<qintptr>(elGetSDKByIndex),
        reinterpret_cast<qintptr>(elGetSDKCount),
        reinterpret_cast<qintptr>(elGetSDKName),
        reinterpret_cast<qintptr>(sdkGetParent),
        reinterpret_cast<qintptr>(elGetInterface),
        reinterpret_cast<qintptr>(elGetInherit),
        reinterpret_cast<qintptr>(resEmpty),
        reinterpret_cast<qintptr>(resSetPref),
        reinterpret_cast<qintptr>(_Error),
        reinterpret_cast<qintptr>(elGetGroup),
        reinterpret_cast<qintptr>(propSaveToFile),
    };

    /*!  Служебные функции   */

    void setProxiedCgt(PCodeGenTools cgt)
    {
        m_cgt = cgt;
    }

    //Получаем массив указателей на функции
    PCodeGenTools getCgt()
    {
        return reinterpret_cast<PCodeGenTools>(proxyCgt);
    }
}
