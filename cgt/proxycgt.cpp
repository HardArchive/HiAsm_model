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
static TCodeGenTools *m_cgt = nullptr;

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

qint32 EXPORT sdkGetCount(qint32 id_sdk)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->sdkGetCount(id_sdk);
    printArgs({id(id_sdk)});
    PRINT_RESULT(res)

    return res;
}
qint32 EXPORT sdkGetElement(qint32 id_sdk, qint32 index)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->sdkGetElement(id_sdk, index);
    printArgs({id(id_sdk), index});
    PRINT_RESULT(id(res))

    return res;
}
qint32 EXPORT sdkGetElementName(qint32 id_sdk, char *name)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->sdkGetElementName(id_sdk, name);
    printArgs({id(id_sdk), str(name)});
    PRINT_RESULT(id(res))

    return res;
}
ElementFlags EXPORT elGetFlag(qint32 id_element)
{
    PRINT_FUNC_INFO
    ElementFlags res = m_cgt->elGetFlag(id_element);
    printArgs({id(id_element)});
    PRINT_RESULT(ElementFlgs(res))

    return res;
}
qint32 EXPORT elGetPropCount(qint32 id_element)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->elGetPropCount(id_element);
    printArgs({id(id_element)});
    PRINT_RESULT(res)

    return res;
}
qint32 EXPORT elGetProperty(qint32 id_element, qint32 index)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->elGetProperty(id_element, index);
    printArgs({id(id_element), index});
    PRINT_RESULT(id(res))

    return res;
}
bool EXPORT elIsDefProp(qint32 id_element, qint32 index)
{
    PRINT_FUNC_INFO
    bool res = m_cgt->elIsDefProp(id_element, index);
    printArgs({id(id_element), index});
    PRINT_RESULT(res)

    return res;
}
qint32 EXPORT elSetCodeName(qint32 id_element, const char *name)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->elSetCodeName(id_element, name);
    printArgs({id(id_element), str(name)});
    PRINT_RESULT(id(res))

    return res;
}
const char *EXPORT elGetCodeName(qint32 id_element)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->elGetCodeName(id_element);
    printArgs({id(id_element)});
    PRINT_RESULT(str(res))

    return res;
}
const char *EXPORT elGetClassName(qint32 id_element)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->elGetClassName(id_element);
    printArgs({id(id_element)});
    PRINT_RESULT(str(res))

    return res;
}
const char *EXPORT elGetInfSub(qint32 id_element)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->elGetInfSub(id_element);
    printArgs({id(id_element)});
    PRINT_RESULT(str(res))

    return res;
}
qint32 EXPORT elGetPtCount(qint32 id_element)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->elGetPtCount(id_element);
    printArgs({id(id_element)});
    PRINT_RESULT(res)

    return res;
}
qint32 EXPORT elGetPt(qint32 id_element, qint32 index)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->elGetPt(id_element, index);
    printArgs({id(id_element), index});
    PRINT_RESULT(id(res))

    return res;
}
qint32 EXPORT elGetPtName(qint32 id_element, const char *name)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->elGetPtName(id_element, name);
    printArgs({id(id_element), str(name)});
    PRINT_RESULT(id(res))

    return res;
}
ElementClass EXPORT elGetClassIndex(qint32 id_element)
{
    PRINT_FUNC_INFO
    ElementClass res = m_cgt->elGetClassIndex(id_element);
    printArgs({id(id_element)});
    PRINT_RESULT(ElementClassMap[res]) //-V108

    return res;
}
qint32 EXPORT elGetSDK(qint32 id_element)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->elGetSDK(id_element);
    printArgs({id(id_element)});
    PRINT_RESULT(id(res))

    return res;
}
bool EXPORT elLinkIs(qint32 id_element)
{
    PRINT_FUNC_INFO
    bool res = m_cgt->elLinkIs(id_element);
    printArgs({id(id_element)});
    PRINT_RESULT(res)

    return res;
}
qint32 EXPORT elLinkMain(qint32 id_element)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->elLinkMain(id_element);
    printArgs({id(id_element)});
    PRINT_RESULT(id(res))

    return res;
}
void EXPORT elGetPos(qint32 id_element, qint32 &X, qint32 &Y)
{
    PRINT_FUNC_INFO
    m_cgt->elGetPos(id_element, X, Y);
    printArgs({id(id_element), X, Y});
}
void EXPORT elGetSize(qint32 id_element, qint32 &W, qint32 &H)
{
    PRINT_FUNC_INFO
    m_cgt->elGetSize(id_element, W, H);
    printArgs({id(id_element), W, H});
}
qint32 EXPORT elGetEID(qint32 id_point)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->elGetEID(id_point);
    printArgs({id(id_point)});
    PRINT_RESULT(res)

    return res;
}
qint32 EXPORT ptGetLinkPoint(qint32 id_point)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->ptGetLinkPoint(id_point);
    printArgs({id(id_point)});
    PRINT_RESULT(id(res))

    return res;
}
qint32 EXPORT ptGetRLinkPoint(qint32 id_point)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->ptGetRLinkPoint(id_point);
    printArgs({id(id_point)});
    PRINT_RESULT(id(res))

    return res;
}
PointType EXPORT ptGetType(qint32 id_point)
{
    PRINT_FUNC_INFO
    PointType res = m_cgt->ptGetType(id_point);
    printArgs({id(id_point)});
    PRINT_RESULT(PointTypeMap[res]) //-V108

    return res;
}
const char *EXPORT ptGetName(qint32 id_point)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->ptGetName(id_point);
    printArgs({id(id_point)});
    PRINT_RESULT(str(res))

    return res;
}
qint32 EXPORT ptGetParent(qint32 id_point)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->ptGetParent(id_point);
    printArgs({id(id_point)});
    PRINT_RESULT(id(res))

    return res;
}
qint32 EXPORT ptGetIndex(qint32 id_point)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->ptGetIndex(id_point);
    printArgs({id(id_point)});
    PRINT_RESULT(res)

    return res;
}
const char *EXPORT pt_dpeGetName(qint32 id_point)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->pt_dpeGetName(id_point);
    printArgs({id(id_point)});
    PRINT_RESULT(str(res))

    return res;
}
DataType EXPORT propGetType(qint32 id_prop)
{
    PRINT_FUNC_INFO
    DataType res = m_cgt->propGetType(id_prop);
    printArgs({id(id_prop)});
    PRINT_RESULT(DataTypeMap[res]) //-V108

    return res;
}
const char *EXPORT propGetName(qint32 id_prop)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->propGetName(id_prop);
    printArgs({id(id_prop)});
    PRINT_RESULT(str(res))

    return res;
}
qint32 EXPORT propGetValue(qint32 id_prop)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->propGetValue(id_prop);
    printArgs({id(id_prop)});
    PRINT_RESULT(id(res))

    return res;
}
uchar EXPORT propToByte(qint32 id_prop)
{
    PRINT_FUNC_INFO
    uchar res = m_cgt->propToByte(id_prop);
    printArgs({id(id_prop)});
    PRINT_RESULT(res)

    return res;
}
qint32 EXPORT propToInteger(qint32 id_prop)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->propToInteger(id_prop);
    printArgs({id(id_prop)});
    PRINT_RESULT(res)

    return res;
}
qreal EXPORT propToReal(qint32 id_prop)
{
    PRINT_FUNC_INFO
    float res = m_cgt->propToReal(id_prop);
    printArgs({id(id_prop)});
    PRINT_RESULT(res)

    return res;
}
const char *EXPORT propToString(qint32 id_prop)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->propToString(id_prop);
    printArgs({id(id_prop)});
    PRINT_RESULT(str(res))

    return res;
}
qint32 EXPORT resAddFile(const char *name)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->resAddFile(name);
    printArgs({str(name)});
    PRINT_RESULT(res)

    return res;
}
const char *EXPORT resAddIcon(qint32 id_prop)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->resAddIcon(id_prop);
    printArgs({id(id_prop)});
    PRINT_RESULT(str(res))

    return res;
}
const char *EXPORT resAddStr(const char *str)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->resAddStr(str);
    printArgs({str});
    PRINT_RESULT(str(res))

    return res;
}
const char *EXPORT resAddStream(qint32 id_prop)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->resAddStream(id_prop);
    printArgs({id(id_prop)});
    PRINT_RESULT(str(res))

    return res;
}
const char *EXPORT resAddWave(qint32 id_prop)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->resAddWave(id_prop);
    printArgs({id(id_prop)});
    PRINT_RESULT(str(res))

    return res;
}
const char *EXPORT resAddBitmap(qint32 id_prop)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->resAddBitmap(id_prop);
    printArgs({id(id_prop)});
    PRINT_RESULT(str(res))

    return res;
}
const char *EXPORT resAddMenu(qint32 id_prop)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->resAddMenu(id_prop);
    printArgs({id(id_prop)});
    PRINT_RESULT(str(res))

    return res;
}
qint32 EXPORT _Debug(const char *text, qint32 color)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->_Debug(text, color);
    printArgs({str(text), color});
    PRINT_RESULT(res)

    return res;
}
qint32 EXPORT GetParam(CgtParams index, void *value)
{
    PRINT_FUNC_INFO
    if (index > 12)
        index = PARAM_DEBUG_MODE;

    qint32 res = m_cgt->GetParam(index, value);

    switch (index) {
    case PARAM_CODE_PATH:
        printParamArgs(index, reinterpret_cast<const char *>(value));
        break;
    case PARAM_DEBUG_MODE:
        printParamArgs(index, *reinterpret_cast<const qint32 *>(value)); //-V206
        break;
    case PARAM_DEBUG_SERVER_PORT:
        printParamArgs(index, *reinterpret_cast<const qint32 *>(value)); //-V206
        break;
    case PARAM_DEBUG_CLIENT_PORT:
        printParamArgs(index, *reinterpret_cast<const qint32 *>(value)); //-V206
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
        printParamArgs(index, *reinterpret_cast<const qint32 *>(value)); //-V206
        break;
    case PARAM_SDE_HEIGHT:
        printParamArgs(index, *reinterpret_cast<const qint32 *>(value)); //-V206
        break;
    case PARAM_COMPILER:
        printParamArgs(index, reinterpret_cast<const char *>(value));
        break;
    }

    PRINT_RESULT(res)

    return res;
}
qint32 EXPORT arrCount(qint32 id_value)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->arrCount(id_value);
    printArgs({id(id_value)});
    PRINT_RESULT(res)

    return res;
}
DataType EXPORT arrType(qint32 id_value)
{
    PRINT_FUNC_INFO
    DataType res = m_cgt->arrType(id_value);
    printArgs({id(id_value)});
    PRINT_RESULT(DataTypeMap[res]) //-V108

    return res;
}
const char *EXPORT arrItemName(qint32 id_value, qint32 index)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->arrItemName(id_value, index);
    printArgs({id(id_value), index});
    PRINT_RESULT(str(res))

    return res;
}
qint32 EXPORT arrItemData(qint32 id_value, qint32 index)
{
    PRINT_FUNC_INFO
    const qint32 res = m_cgt->arrItemData(id_value, index);
    printArgs({id(id_value), index});
    PRINT_RESULT(id(res))

    return res;
}
qint32 EXPORT arrGetItem(qint32 id_value, qint32 index)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->arrGetItem(id_value, index);
    printArgs({id(id_value), index});
    PRINT_RESULT(id(res))

    return res;
}
qint32 EXPORT isDebug(qint32 id_element)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->isDebug(id_element);
    printArgs({id(id_element)});
    PRINT_RESULT(res)

    return res;
}
DataType EXPORT dtType(qint32 id_value)
{
    PRINT_FUNC_INFO
    DataType res = m_cgt->dtType(id_value);
    printArgs({id(id_value)});
    PRINT_RESULT(DataTypeMap[res]) //-V108

    return res;
}
const char *EXPORT dtStr(qint32 id_value)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->dtStr(id_value);
    printArgs({id(id_value)});
    PRINT_RESULT(str(res))

    return res;
}
qint32 EXPORT dtInt(qint32 id_value)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->dtInt(id_value);
    printArgs({id(id_value)});
    PRINT_RESULT(res)

    return res;
}
qreal EXPORT dtReal(qint32 id_value)
{
    PRINT_FUNC_INFO
    qreal res = m_cgt->dtReal(id_value);
    printArgs({id(id_value)});
    PRINT_RESULT(res)

    return res;
}
const char *EXPORT fntName(qint32 id_value)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->fntName(id_value);
    printArgs({id(id_value)});
    PRINT_RESULT(res)

    return res;
}
qint32 EXPORT fntSize(qint32 id_value)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->fntSize(id_value);
    printArgs({id(id_value)});
    PRINT_RESULT(res)

    return res;
}
uchar EXPORT fntStyle(qint32 id_value)
{
    printArgs({id(id_value)});
    PRINT_FUNC_INFO
    uchar res = m_cgt->fntStyle(id_value);
    PRINT_RESULT(res)

    return res;
}
uint EXPORT fntColor(qint32 id_value)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->fntColor(id_value);
    printArgs({id(id_value)});
    PRINT_RESULT(res)

    return res;
}
uchar EXPORT fntCharSet(qint32 id_value)
{
    PRINT_FUNC_INFO
    uchar res = m_cgt->fntCharSet(id_value);
    printArgs({id(id_value)});
    PRINT_RESULT(res)

    return res;
}
qint32 EXPORT elGetData(qint32 id_element)
{
    PRINT_FUNC_INFO
    const qint32 res = m_cgt->elGetData(id_element);
    printArgs({id(id_element)});
    PRINT_RESULT(p(res))

    return res;
}
void EXPORT elSetData(qint32 id_element, qint32 data)
{
    PRINT_FUNC_INFO
    m_cgt->elSetData(id_element, data);
    printArgs({id(id_element), p(data)});
}
DataType EXPORT ptGetDataType(qint32 id_point)
{
    PRINT_FUNC_INFO
    DataType res = m_cgt->ptGetDataType(id_point);
    printArgs({id(id_point)});
    PRINT_RESULT(DataTypeMap[res]) //-V108

    return res;
}
qint32 EXPORT elGetParent(qint32 id_element)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->elGetParent(id_element);
    printArgs({id(id_element)});
    PRINT_RESULT(id(res))

    return res;
}
qint32 EXPORT elGetPropertyListCount(qint32 id_element)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->elGetPropertyListCount(id_element);
    printArgs({id(id_element)});
    PRINT_RESULT(res)

    return res;
}
qint32 EXPORT elGetPropertyListItem(qint32 id_element, qint32 index)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->elGetPropertyListItem(id_element, index);
    printArgs({id(id_element), index});
    PRINT_RESULT(id(res))

    return res;
}
const char *EXPORT plGetName(qint32 id_point)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->plGetName(id_point);
    printArgs({id(id_point)});
    PRINT_RESULT(str(res))

    return res;
}
const char *EXPORT plGetInfo(qint32 id_point)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->plGetInfo(id_point);
    printArgs({id(id_point)});
    PRINT_RESULT(str(res))

    return res;
}
const char *EXPORT plGetGroup(qint32 id_point)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->plGetGroup(id_point);
    printArgs({id(id_point)});
    PRINT_RESULT(str(res))

    return res;
}
qint32 EXPORT plGetProperty(qint32 id_point)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->plGetProperty(id_point);
    printArgs({id(id_point)});
    PRINT_RESULT(id(res))

    return res;
}
qint32 EXPORT plGetOwner(qint32 id_prop)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->plGetOwner(id_prop);
    printArgs({id(id_prop)});
    PRINT_RESULT(id(res))

    return res;
}
const char *EXPORT ptGetInfo(qint32 id_prop)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->ptGetInfo(id_prop);
    printArgs({id(id_prop)});
    PRINT_RESULT(str(res))

    return res;
}
qint32 EXPORT propGetLinkedElement(qint32 id_prop, const char *propName)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->propGetLinkedElement(id_prop, propName);
    printArgs({id(id_prop), str(propName)});
    PRINT_RESULT(id(res))

    return res;
}
qint32 EXPORT propIsTranslate(qint32 id_element, qint32 id_prop)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->propIsTranslate(id_element, id_prop);
    printArgs({id(id_element), id(id_prop)});
    PRINT_RESULT(res)

    return res;
}
qint32 EXPORT propGetLinkedElementInfo(qint32 id_element, qint32 id_prop, char *info)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->propGetLinkedElementInfo(id_element, id_prop, info);
    printArgs({id(id_element), id(id_prop), str(info)});
    PRINT_RESULT(id(res))

    return 0;
}
qint32 EXPORT elGetSDKByIndex(qint32 id_element, qint32 index)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->elGetSDKByIndex(id_element, index);
    printArgs({id(id_element), index});
    PRINT_RESULT(id(res))

    return res;
}
qint32 EXPORT elGetSDKCount(qint32 id_element)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->elGetSDKCount(id_element);
    printArgs({id(id_element)});
    PRINT_RESULT(res)

    return res;
}
const char *EXPORT elGetSDKName(qint32 id_element, qint32 index)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->elGetSDKName(id_element, index);
    printArgs({id(id_element), index});
    PRINT_RESULT(str(res))

    return res;
}
qint32 EXPORT sdkGetParent(qint32 id_sdk)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->sdkGetParent(id_sdk);
    printArgs({id(id_sdk)});
    PRINT_RESULT(id(res))

    return res;
}
const char *EXPORT elGetInterface(qint32 id_element)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->elGetInterface(id_element);
    printArgs({id(id_element)});
    PRINT_RESULT(str(res))

    return res;
}
const char *EXPORT elGetInherit(qint32 id_element)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->elGetInherit(id_element);
    printArgs({id(id_element)});
    PRINT_RESULT(str(res))

    return res;
}
qint32 EXPORT resEmpty()
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->resEmpty();
    PRINT_RESULT(res)

    return res;
}
qint32 EXPORT resSetPref(const char *pref)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->resSetPref(pref);
    printArgs({str(pref)});
    PRINT_RESULT(res)

    return res;
}
qint32 EXPORT _Error(qint32 line, qint32 id_element, const char *text)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->_Error(line, id_element, text);
    printArgs({line, id(id_element), str(text)});
    PRINT_RESULT(res)

    return res;
}
qint32 EXPORT elGetGroup(qint32 id_element)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->elGetGroup(id_element);
    printArgs({id(id_element)});
    PRINT_RESULT(res)

    return res;
}
qint32 EXPORT propSaveToFile(qint32 id_prop, const char *fileName)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->propSaveToFile(id_prop, fileName);
    printArgs({id(id_prop), str(fileName)});
    PRINT_RESULT(res)

    return res;
}

static qintptr proxyCgt[]{
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

void setProxiedCgt(TCodeGenTools *cgt)
{
    m_cgt = cgt;
}

//Получаем массив указателей на функции
TCodeGenTools *getCgt()
{
    return reinterpret_cast<TCodeGenTools *>(proxyCgt);
}
}
