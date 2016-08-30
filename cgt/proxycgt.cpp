//Project
#include "proxycgt.h"

//STL

//Qt
#include <QDebug>
#include <QFlags>

namespace ProxyCgt {
//Дефайны
#define EXPORT __stdcall
#define PRINT_FUNC_INFO qInfo("  Call: %s", Q_FUNC_INFO);
#define PRINT_RESULT(X) qInfo().noquote() << "  Return:" << X;

#define id(X) QString("id(%1)").arg(X)
#define str(X) QString("\"%1\"").arg(QString::fromLocal8Bit(X))
#define p(X) QString("p(%1)").arg(X)

//Для хранения указателя на массив указателей на callback функции
static TCodeGenTools * m_cgt = nullptr;

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

EXPORT qint32 sdkGetCount(qint32 id_sdk)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->sdkGetCount(id_sdk);
    printArgs({ id(id_sdk) });
    PRINT_RESULT(res)

    return res;
}
EXPORT qint32 sdkGetElement(qint32 id_sdk, qint32 index)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->sdkGetElement(id_sdk, index);
    printArgs({ id(id_sdk), index });
    PRINT_RESULT(id(res))

    return res;
}
EXPORT qint32 sdkGetElementName(qint32 id_sdk, char *name)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->sdkGetElementName(id_sdk, name);
    printArgs({ id(id_sdk), str(name) });
    PRINT_RESULT(id(res))

    return res;
}
EXPORT ElementFlags elGetFlag(qint32 id_element)
{
    PRINT_FUNC_INFO
    ElementFlags res = m_cgt->elGetFlag(id_element);
    printArgs({ id(id_element) });
    PRINT_RESULT(ElementFlgs(res))

    return res;
}
EXPORT qint32 elGetPropCount(qint32 id_element)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->elGetPropCount(id_element);
    printArgs({ id(id_element) });
    PRINT_RESULT(res)

    return res;
}
EXPORT qint32 elGetProperty(qint32 id_element, qint32 index)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->elGetProperty(id_element, index);
    printArgs({ id(id_element), index });
    PRINT_RESULT(id(res))

    return res;
}
EXPORT bool elIsDefProp(qint32 id_element, qint32 index)
{
    PRINT_FUNC_INFO
    bool res = m_cgt->elIsDefProp(id_element, index);
    printArgs({ id(id_element), index });
    PRINT_RESULT(res)

    return res;
}
EXPORT qint32 elSetCodeName(qint32 id_element, const char *name)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->elSetCodeName(id_element, name);
    printArgs({ id(id_element), str(name) });
    PRINT_RESULT(id(res))

    return res;
}
EXPORT const char *elGetCodeName(qint32 id_element)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->elGetCodeName(id_element);
    printArgs({ id(id_element) });
    PRINT_RESULT(str(res))

    return res;
}
EXPORT const char *elGetClassName(qint32 id_element)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->elGetClassName(id_element);
    printArgs({ id(id_element) });
    PRINT_RESULT(str(res))

    return res;
}
EXPORT const char *elGetInfSub(qint32 id_element)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->elGetInfSub(id_element);
    printArgs({ id(id_element) });
    PRINT_RESULT(str(res))

    return res;
}
EXPORT qint32 elGetPtCount(qint32 id_element)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->elGetPtCount(id_element);
    printArgs({ id(id_element) });
    PRINT_RESULT(res)

    return res;
}
EXPORT qint32 elGetPt(qint32 id_element, qint32 index)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->elGetPt(id_element, index);
    printArgs({ id(id_element), index });
    PRINT_RESULT(id(res))

    return res;
}
EXPORT qint32 elGetPtName(qint32 id_element, const char *name)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->elGetPtName(id_element, name);
    printArgs({ id(id_element), str(name) });
    PRINT_RESULT(id(res))

    return res;
}
EXPORT ElementClass elGetClassIndex(qint32 id_element)
{
    PRINT_FUNC_INFO
    ElementClass res = m_cgt->elGetClassIndex(id_element);
    printArgs({ id(id_element) });
    PRINT_RESULT(ElementClassMap[res]) //-V108

    return res;
}
EXPORT qint32 elGetSDK(qint32 id_element)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->elGetSDK(id_element);
    printArgs({ id(id_element) });
    PRINT_RESULT(id(res))

    return res;
}
EXPORT bool elLinkIs(qint32 id_element)
{
    PRINT_FUNC_INFO
    bool res = m_cgt->elLinkIs(id_element);
    printArgs({ id(id_element) });
    PRINT_RESULT(res)

    return res;
}
EXPORT qint32 elLinkMain(qint32 id_element)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->elLinkMain(id_element);
    printArgs({ id(id_element) });
    PRINT_RESULT(id(res))

    return res;
}
EXPORT void elGetPos(qint32 id_element, qint32 &X, qint32 &Y)
{
    PRINT_FUNC_INFO
    m_cgt->elGetPos(id_element, X, Y);
    printArgs({ id(id_element), X, Y });
}
EXPORT void elGetSize(qint32 id_element, qint32 &W, qint32 &H)
{
    PRINT_FUNC_INFO
    m_cgt->elGetSize(id_element, W, H);
    printArgs({ id(id_element), W, H });
}
EXPORT qint32 elGetEID(qint32 id_point)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->elGetEID(id_point);
    printArgs({ id(id_point) });
    PRINT_RESULT(res)

    return res;
}
EXPORT qint32 ptGetLinkPoint(qint32 id_point)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->ptGetLinkPoint(id_point);
    printArgs({ id(id_point) });
    PRINT_RESULT(id(res))

    return res;
}
EXPORT qint32 ptGetRLinkPoint(qint32 id_point)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->ptGetRLinkPoint(id_point);
    printArgs({ id(id_point) });
    PRINT_RESULT(id(res))

    return res;
}
EXPORT PointType ptGetType(qint32 id_point)
{
    PRINT_FUNC_INFO
    PointType res = m_cgt->ptGetType(id_point);
    printArgs({ id(id_point) });
    PRINT_RESULT(PointTypeMap[res]) //-V108

    return res;
}
EXPORT const char *ptGetName(qint32 id_point)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->ptGetName(id_point);
    printArgs({ id(id_point) });
    PRINT_RESULT(str(res))

    return res;
}
EXPORT qint32 ptGetParent(qint32 id_point)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->ptGetParent(id_point);
    printArgs({ id(id_point) });
    PRINT_RESULT(id(res))

    return res;
}
EXPORT qint32 ptGetIndex(qint32 id_point)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->ptGetIndex(id_point);
    printArgs({ id(id_point) });
    PRINT_RESULT(res)

    return res;
}
EXPORT const char *pt_dpeGetName(qint32 id_point)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->pt_dpeGetName(id_point);
    printArgs({ id(id_point) });
    PRINT_RESULT(str(res))

    return res;
}
EXPORT DataType propGetType(qint32 id_prop)
{
    PRINT_FUNC_INFO
    DataType res = m_cgt->propGetType(id_prop);
    printArgs({ id(id_prop) });
    PRINT_RESULT(DataTypeMap[res]) //-V108

    return res;
}
EXPORT const char *propGetName(qint32 id_prop)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->propGetName(id_prop);
    printArgs({ id(id_prop) });
    PRINT_RESULT(str(res))

    return res;
}
EXPORT qint32 propGetValue(qint32 id_prop)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->propGetValue(id_prop);
    printArgs({ id(id_prop) });
    PRINT_RESULT(id(res))

    return res;
}
EXPORT uchar propToByte(qint32 id_prop)
{
    PRINT_FUNC_INFO
    uchar res = m_cgt->propToByte(id_prop);
    printArgs({ id(id_prop) });
    PRINT_RESULT(res)

    return res;
}
EXPORT qint32 propToInteger(qint32 id_prop)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->propToInteger(id_prop);
    printArgs({ id(id_prop) });
    PRINT_RESULT(res)

    return res;
}
EXPORT qreal propToReal(qint32 id_prop)
{
    PRINT_FUNC_INFO
    float res = m_cgt->propToReal(id_prop);
    printArgs({ id(id_prop) });
    PRINT_RESULT(res)

    return res;
}
EXPORT const char *propToString(qint32 id_prop)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->propToString(id_prop);
    printArgs({ id(id_prop) });
    PRINT_RESULT(str(res))

    return res;
}
EXPORT qint32 resAddFile(const char *name)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->resAddFile(name);
    printArgs({ str(name) });
    PRINT_RESULT(res)

    return res;
}
EXPORT const char *resAddIcon(qint32 id_prop)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->resAddIcon(id_prop);
    printArgs({ id(id_prop) });
    PRINT_RESULT(str(res))

    return res;
}
EXPORT const char *resAddStr(const char *str)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->resAddStr(str);
    printArgs({ str });
    PRINT_RESULT(str(res))

    return res;
}
EXPORT const char *resAddStream(qint32 id_prop)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->resAddStream(id_prop);
    printArgs({ id(id_prop) });
    PRINT_RESULT(str(res))

    return res;
}
EXPORT const char *resAddWave(qint32 id_prop)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->resAddWave(id_prop);
    printArgs({ id(id_prop) });
    PRINT_RESULT(str(res))

    return res;
}
EXPORT const char *resAddBitmap(qint32 id_prop)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->resAddBitmap(id_prop);
    printArgs({ id(id_prop) });
    PRINT_RESULT(str(res))

    return res;
}
EXPORT const char *resAddMenu(qint32 id_prop)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->resAddMenu(id_prop);
    printArgs({ id(id_prop) });
    PRINT_RESULT(str(res))

    return res;
}
EXPORT qint32 _Debug(const char *text, qint32 color)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->_Debug(text, color);
    printArgs({ str(text), color });
    PRINT_RESULT(res)

    return res;
}
EXPORT qint32 GetParam(CgtParams index, void *value)
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
EXPORT qint32 arrCount(qint32 id_value)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->arrCount(id_value);
    printArgs({ id(id_value) });
    PRINT_RESULT(res)

    return res;
}
EXPORT DataType arrType(qint32 id_value)
{
    PRINT_FUNC_INFO
    DataType res = m_cgt->arrType(id_value);
    printArgs({ id(id_value) });
    PRINT_RESULT(DataTypeMap[res]) //-V108

    return res;
}
EXPORT const char *arrItemName(qint32 id_value, qint32 index)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->arrItemName(id_value, index);
    printArgs({ id(id_value), index });
    PRINT_RESULT(str(res))

    return res;
}
EXPORT qint32 arrItemData(qint32 id_value, qint32 index)
{
    PRINT_FUNC_INFO
    const qint32 res = m_cgt->arrItemData(id_value, index);
    printArgs({ id(id_value), index });
    PRINT_RESULT(id(res))

    return res;
}
EXPORT qint32 arrGetItem(qint32 id_value, qint32 index)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->arrGetItem(id_value, index);
    printArgs({ id(id_value), index });
    PRINT_RESULT(id(res))

    return res;
}
EXPORT qint32 isDebug(qint32 id_element)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->isDebug(id_element);
    printArgs({ id(id_element) });
    PRINT_RESULT(res)

    return res;
}
EXPORT DataType dtType(qint32 id_value)
{
    PRINT_FUNC_INFO
    DataType res = m_cgt->dtType(id_value);
    printArgs({ id(id_value) });
    PRINT_RESULT(DataTypeMap[res]) //-V108

    return res;
}
EXPORT const char *dtStr(qint32 id_value)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->dtStr(id_value);
    printArgs({ id(id_value) });
    PRINT_RESULT(str(res))

    return res;
}
EXPORT qint32 dtInt(qint32 id_value)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->dtInt(id_value);
    printArgs({ id(id_value) });
    PRINT_RESULT(res)

    return res;
}
EXPORT qreal dtReal(qint32 id_value)
{
    PRINT_FUNC_INFO
    qreal res = m_cgt->dtReal(id_value);
    printArgs({ id(id_value) });
    PRINT_RESULT(res)

    return res;
}
EXPORT const char *fntName(qint32 id_value)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->fntName(id_value);
    printArgs({ id(id_value) });
    PRINT_RESULT(res)

    return res;
}
EXPORT qint32 fntSize(qint32 id_value)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->fntSize(id_value);
    printArgs({ id(id_value) });
    PRINT_RESULT(res)

    return res;
}
EXPORT uchar fntStyle(qint32 id_value)
{
    printArgs({ id(id_value) });
    PRINT_FUNC_INFO
    uchar res = m_cgt->fntStyle(id_value);
    PRINT_RESULT(res)

    return res;
}
EXPORT uint fntColor(qint32 id_value)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->fntColor(id_value);
    printArgs({ id(id_value) });
    PRINT_RESULT(res)

    return res;
}
EXPORT uchar fntCharSet(qint32 id_value)
{
    PRINT_FUNC_INFO
    uchar res = m_cgt->fntCharSet(id_value);
    printArgs({ id(id_value) });
    PRINT_RESULT(res)

    return res;
}
EXPORT qint32 elGetData(qint32 id_element)
{
    PRINT_FUNC_INFO
    const qint32 res = m_cgt->elGetData(id_element);
    printArgs({ id(id_element) });
    PRINT_RESULT(p(res))

    return res;
}
EXPORT void elSetData(qint32 id_element, qint32 data)
{
    PRINT_FUNC_INFO
    m_cgt->elSetData(id_element, data);
    printArgs({ id(id_element), p(data) });
}
EXPORT DataType ptGetDataType(qint32 id_point)
{
    PRINT_FUNC_INFO
    DataType res = m_cgt->ptGetDataType(id_point);
    printArgs({ id(id_point) });
    PRINT_RESULT(DataTypeMap[res]) //-V108

    return res;
}
EXPORT qint32 elGetParent(qint32 id_element)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->elGetParent(id_element);
    printArgs({ id(id_element) });
    PRINT_RESULT(id(res))

    return res;
}
EXPORT qint32 elGetPropertyListCount(qint32 id_element)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->elGetPropertyListCount(id_element);
    printArgs({ id(id_element) });
    PRINT_RESULT(res)

    return res;
}
EXPORT qint32 elGetPropertyListItem(qint32 id_element, qint32 index)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->elGetPropertyListItem(id_element, index);
    printArgs({ id(id_element), index });
    PRINT_RESULT(id(res))

    return res;
}
EXPORT const char *plGetName(qint32 id_point)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->plGetName(id_point);
    printArgs({ id(id_point) });
    PRINT_RESULT(str(res))

    return res;
}
EXPORT const char *plGetInfo(qint32 id_point)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->plGetInfo(id_point);
    printArgs({ id(id_point) });
    PRINT_RESULT(str(res))

    return res;
}
EXPORT const char *plGetGroup(qint32 id_point)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->plGetGroup(id_point);
    printArgs({ id(id_point) });
    PRINT_RESULT(str(res))

    return res;
}
EXPORT qint32 plGetProperty(qint32 id_point)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->plGetProperty(id_point);
    printArgs({ id(id_point) });
    PRINT_RESULT(id(res))

    return res;
}
EXPORT qint32 plGetOwner(qint32 id_prop)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->plGetOwner(id_prop);
    printArgs({ id(id_prop) });
    PRINT_RESULT(id(res))

    return res;
}
EXPORT const char *ptGetInfo(qint32 id_prop)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->ptGetInfo(id_prop);
    printArgs({ id(id_prop) });
    PRINT_RESULT(str(res))

    return res;
}
EXPORT qint32 propGetLinkedElement(qint32 id_prop, const char *propName)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->propGetLinkedElement(id_prop, propName);
    printArgs({ id(id_prop), str(propName) });
    PRINT_RESULT(id(res))

    return res;
}
EXPORT qint32 propIsTranslate(qint32 id_element, qint32 id_prop)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->propIsTranslate(id_element, id_prop);
    printArgs({ id(id_element), id(id_prop) });
    PRINT_RESULT(res)

    return res;
}
EXPORT qint32 propGetLinkedElementInfo(qint32 id_element, qint32 id_prop, char *info)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->propGetLinkedElementInfo(id_element, id_prop, info);
    printArgs({ id(id_element), id(id_prop), str(info) });
    PRINT_RESULT(id(res))

    return 0;
}
EXPORT qint32 elGetSDKByIndex(qint32 id_element, qint32 index)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->elGetSDKByIndex(id_element, index);
    printArgs({ id(id_element), index });
    PRINT_RESULT(id(res))

    return res;
}
EXPORT qint32 elGetSDKCount(qint32 id_element)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->elGetSDKCount(id_element);
    printArgs({ id(id_element) });
    PRINT_RESULT(res)

    return res;
}
EXPORT const char *elGetSDKName(qint32 id_element, qint32 index)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->elGetSDKName(id_element, index);
    printArgs({ id(id_element), index });
    PRINT_RESULT(str(res))

    return res;
}
EXPORT qint32 sdkGetParent(qint32 id_sdk)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->sdkGetParent(id_sdk);
    printArgs({ id(id_sdk) });
    PRINT_RESULT(id(res))

    return res;
}
EXPORT const char *elGetInterface(qint32 id_element)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->elGetInterface(id_element);
    printArgs({ id(id_element) });
    PRINT_RESULT(str(res))

    return res;
}
EXPORT const char *elGetInherit(qint32 id_element)
{
    PRINT_FUNC_INFO
    const char *res = m_cgt->elGetInherit(id_element);
    printArgs({ id(id_element) });
    PRINT_RESULT(str(res))

    return res;
}
EXPORT qint32 resEmpty()
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->resEmpty();
    PRINT_RESULT(res)

    return res;
}
EXPORT qint32 resSetPref(const char *pref)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->resSetPref(pref);
    printArgs({ str(pref) });
    PRINT_RESULT(res)

    return res;
}
EXPORT qint32 _Error(qint32 line, qint32 id_element, const char *text)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->_Error(line, id_element, text);
    printArgs({ line, id(id_element), str(text) });
    PRINT_RESULT(res)

    return res;
}
EXPORT qint32 elGetGroup(qint32 id_element)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->elGetGroup(id_element);
    printArgs({ id(id_element) });
    PRINT_RESULT(res)

    return res;
}
EXPORT qint32 propSaveToFile(qint32 id_prop, const char *fileName)
{
    PRINT_FUNC_INFO
    qint32 res = m_cgt->propSaveToFile(id_prop, fileName);
    printArgs({ id(id_prop), str(fileName) });
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
TCodeGenTools * getCgt()
{
    return reinterpret_cast<TCodeGenTools *>(proxyCgt);
}
}
