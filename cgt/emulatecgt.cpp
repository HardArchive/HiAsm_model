//Project
#include "emulatecgt.h"
#include "cgt.h"
#include "scenemodel/container.h"
#include "scenemodel/element.h"
#include "scenemodel/point.h"
#include "scenemodel/property.h"
#include "scenemodel/valuetypes.h"

//STL

//Qt

namespace EmulateCgt {
#define EXPORT __stdcall

//ru Храним указатель на модель данных
static SceneModel *m_model = nullptr;

//~~~~~~~~~~~~~~~~~ Проксированные функции ~~~~~~~~~~~~~~~~~~~

//!~~~~~~~~~~~~~~~~~~~~~~~~ контейнер ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает количество элементов в контейнере.
EXPORT int sdkGetCount(qintptr id_sdk)
{
    return m_model->getCountElementsInContainer(id_sdk);
}

//ru Возвращает ID элемента по его Z-положению(индексу) в контейнере.
EXPORT qintptr sdkGetElement(qintptr id_sdk, int index)
{
    return m_model->getIdElementFromSDKByIndex(id_sdk, index);
}

//ru Возвращает ID элемента по имени элемента.
EXPORT qintptr sdkGetElementName(qintptr id_sdk, char *name)
{
    const PContainer c = m_model->getContainerById(id_sdk);
    if (!c)
        return 0;

    return c->getIdElementByName(QString::fromLocal8Bit(name));
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ элемент ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает флаги элемента.
EXPORT ElementFlags elGetFlag(qintptr id_element)
{
    const PElement e = m_model->getElementById(id_element);
    if (!e)
        return ELEMENT_FLG_IS_FREEZE;

    return e->getFlags();
}

//ru Возвращает количество свойств элемента.
EXPORT int elGetPropCount(qintptr id_element)
{
    const PElement e = m_model->getElementById(id_element);
    if (!e)
        return 0;

    return e->getCountProps();
}

//ru Возвращает id свойства элемента по индексу, с порядковым номером из INI.
EXPORT qintptr elGetProperty(qintptr id_element, int index)
{
    const PElement e = m_model->getElementById(id_element);
    if (!e)
        return 0;

    return e->getIdPropertyByIndex(index);
}

//ru Возвращает True, если значение свойства совпадает с заданным в INI файле, иначе False.
EXPORT bool elIsDefProp(qintptr id_element, int index)
{
    const PElement e = m_model->getElementById(id_element);
    if (!e)
        return false;

    PProperty p = e->getPropertyByIndex(index);
    if (!p)
        return false;

    return p->getIsDefProp();
}

//ru Присваиваем элементу уникальное имя и возвращаем ID этого элемента.
EXPORT qintptr elSetCodeName(qintptr id_element, const char *name)
{
    const PElement e = m_model->getElementById(id_element);
    if (!e)
        return 0;

    e->setCodeName(QString::fromLocal8Bit(name));
    return id_element;
}

//ru Возвращает уникальное имя элемента
EXPORT const char *elGetCodeName(qintptr id_element)
{
    const PElement e = m_model->getElementById(id_element);
    if (!e)
        return nullptr;

    return fcgt::strToCString(e->getCodeName());
}

//ru Возвращает имя класса элемента
EXPORT const char *elGetClassName(qintptr id_element)
{
    const PElement e = m_model->getElementById(id_element);
    if (!e)
        return nullptr;

    return fcgt::strToCString(e->getClassName());
}

//ru Возвращает водержимое поля Sub из конфигурационного INI-файла элемента.
EXPORT const char *elGetInfSub(qintptr id_element)
{
    const PElement e = m_model->getElementById(id_element);
    if (!e)
        return 0;

    return fcgt::strToCString(e->getInfSub());
}

//ru Возвращает общее количество видимых точек у элемента.
EXPORT int elGetPtCount(qintptr id_element)
{
    const PElement e = m_model->getElementById(id_element);
    if (!e)
        return 0;

    return e->getCountPoints();
}

//ru Возвращает ID точки по её индексу.
EXPORT qintptr elGetPt(qintptr id_element, int index)
{
    const PElement e = m_model->getElementById(id_element);
    if (!e)
        return 0;

    return e->getIdPointByIndex(index);
}

//ru Возвращает ID точки по её имени.
EXPORT qintptr elGetPtName(qintptr id_element, const char *name)
{
    const PElement e = m_model->getElementById(id_element);
    if (!e)
        return 0;

    return e->getIdPointByName(QString::fromLocal8Bit(name));
}

//ru Возвращает индекс класса элемента.
EXPORT ElementClass elGetClassIndex(qintptr id_element)
{
    const PElement e = m_model->getElementById(id_element);
    if (!e)
        return CI_Element;

    return e->getClassIndex();
}

//ru Получаем ID контейнера из элемента.
//ru Если элемент не содержит контейнеры, возвращаем ID элемента родителя текущего контейнера.
EXPORT qintptr elGetSDK(qintptr id_element)
{
    const PElement e = m_model->getElementById(id_element);
    if (!e)
        return 0;

    const PContainer c = e->getContainer();
    if (!c) {
        const PElement p = qobject_cast<PElement>(e->parent()->parent());
        if (p) {
            return p->getId();
        }
    }

    return c->getId();
}

//ru Возвращает True, если данный элемент является ссылкой, либо на него ссылаются.
EXPORT bool elLinkIs(qintptr id_element)
{
    const PElement e = m_model->getElementById(id_element);
    if (!e)
        return false;

    return e->getLinkIs();
}

//ru Возвращает ID главного элемента(тот, на который ссылаются другие).
EXPORT qintptr elLinkMain(qintptr id_element)
{
    const PElement e = m_model->getElementById(id_element);
    if (!e)
        return 0;

    return e->getLinkIs();
}

//ru Помещает в переменные "X" и "Y", позицию элемента в редакторе схем.
EXPORT void elGetPos(qintptr id_element, int &X, int &Y)
{
    const PElement e = m_model->getElementById(id_element);
    if (!e)
        return;

    X = e->getPosX();
    Y = e->getPosY();
}

//ru Помещает в переменные "w" и "h", размеры элемента.
EXPORT void elGetSize(qintptr id_element, int &W, int &H)
{
    const PElement e = m_model->getElementById(id_element);
    if (!e)
        return;

    W = e->getSizeW();
    H = e->getSizeH();
}

//ru Возвращает внутренний ID элемента (отличается от внешнего).
//[deprecated]
EXPORT int elGetEID(qintptr id_element)
{
    Q_UNUSED(id_element)
    return 0;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ точки элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Получаем ID точки с которой соединена указанная.
EXPORT qintptr ptGetLinkPoint(qintptr id_point)
{
    const PPoint p = m_model->getPointById(id_point);
    if (!p)
        return 0;

    return p->getLinkPoint();
}

//ru Получаем ID точки с которой соединена указанная,
//ru без учета точек разрыва и хабов.
EXPORT qintptr ptGetRLinkPoint(qintptr id_point)
{
    const PPoint p = m_model->getPointById(id_point);
    if (!p)
        return 0;

    return p->getRLinkPoint();
}

//ru Получаем тип точки.
EXPORT PointType ptGetType(qintptr id_point)
{
    const PPoint p = m_model->getPointById(id_point);
    if (!p)
        return pt_Work;

    return p->getType();
}

//ru Возвращает имя точки.
EXPORT const char *ptGetName(qintptr id_point)
{
    const PPoint p = m_model->getPointById(id_point);
    if (!p)
        return nullptr;

    return fcgt::strToCString(p->getName());
}

//ru Получаем ID родителя (элемент) точки.
EXPORT qintptr ptGetParent(qintptr id_point)
{
    const PPoint p = m_model->getPointById(id_point);
    if (!p)
        return 0;
    const PElement e = qobject_cast<PElement>(p->parent());

    return e->getId();
}

//ru Получаем индекс точки относительно точек того же типа.
EXPORT int ptGetIndex(qintptr id_point)
{
    const PPoint p = m_model->getPointById(id_point);
    if (!p)
        return 0;

    return p->getIndex();
}

//ru Возвращает базовую часть имени динамической точки(для CI_DPElement).
EXPORT const char *pt_dpeGetName(qintptr id_point)
{
    const PPoint p = m_model->getPointById(id_point);
    if (!p)
        return nullptr;

    return fcgt::strToCString(p->getDpeName());
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ свойства элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает тип свойства.
EXPORT DataType propGetType(qintptr id_prop)
{
    PProperty p = m_model->getPropertyById(id_prop);
    if (!p)
        return data_null;

    return p->getType();
}

//ru Возвращает имя свойства.
EXPORT const char *propGetName(qintptr id_prop)
{
    PProperty p = m_model->getPropertyById(id_prop);
    if (!p)
        return nullptr;

    return fcgt::strToCString(p->getName());
}

//ru Возвращает значение свойства в виде указателя на данные.
EXPORT qintptr propGetValue(qintptr id_prop)
{
    PProperty p = m_model->getPropertyById(id_prop);
    if (!p)
        return 0;

    const PValue v = p->getValue();
    if (!v)
        return 0;

    return (qintptr)v;
}

//ru Возвращает значение свойства в формате uchar.
EXPORT uchar propToByte(qintptr id_prop)
{
    PProperty p = m_model->getPropertyById(id_prop);
    if (!p)
        return 0;

    return p->toByte();
}

//ru Возвращает значение свойства в формате int.
EXPORT int propToInteger(qintptr id_prop)
{
    PProperty p = m_model->getPropertyById(id_prop);
    if (!p)
        return 0;

    return p->toInt();
}

//ru Возвращает значение свойства в формате float.
EXPORT qreal propToReal(qintptr id_prop)
{
    PProperty p = m_model->getPropertyById(id_prop);
    if (!p)
        return 0;

    return p->toReal();
}

//ru Возвращает значение свойства в виде C строки.
EXPORT const char *propToString(qintptr id_prop)
{
    PProperty p = m_model->getPropertyById(id_prop);
    if (!p)
        return 0;

    return fcgt::strToCString(p->toString());
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ ресурсы ~~~~~~~~~~~~~~~~~~~~~~~~~~

//ru Добавляет имя файла в список временных файлов
//ru для последующего удаления файла.
EXPORT int resAddFile(const char *filePath)
{
    return m_model->addResList(QString::fromLocal8Bit(filePath));
}

//ru Добавляет иконку в ресурсы и в список временных файлов,
//ru и возвращают имя временного файла.
EXPORT const char *resAddIcon(qintptr id_prop)
{
    return m_model->addStreamRes(id_prop);
}

//ru Добавляет строку в ресурсы и в список временных файлов.
//ru Возвращают имя временного файла.
EXPORT const char *resAddStr(const char *string)
{
    return m_model->addStringRes(QString::fromLocal8Bit(string));
}

//ru Добавляет поток (данные) в ресурсы и в список временных файлов,
//ru и возвращает имя временного файла.
//ru Временный файл создаётся в папке %HiAsm%\compiler и существует до конца
//ru работы с библиотекой.
EXPORT const char *resAddStream(qintptr id_prop)
{
    return m_model->addStreamRes(id_prop);
}

//ru Добавляет звук в ресурсы и в список временных файлов,
//ru и возвращает имя временного файла.
//ru Временный файл создаётся в папке %HiAsm%\compiler и существует до конца
//ru работы с библиотекой.
EXPORT const char *resAddWave(qintptr id_prop)
{
    return m_model->addStreamRes(id_prop);
}

//ru Добавляет картинку в ресурсы и в список временных файлов,
//ru и возвращает имя временного файла.
//ru Временный файл создаётся в папке %HiAsm%\compiler и существует до конца
//ru работы с библиотекой.
EXPORT const char *resAddBitmap(qintptr id_prop)
{
    return m_model->addStreamRes(id_prop);
}

//ru Добавляет меню в ресурсы и в список временных файлов.
//[deprecated]
EXPORT const char *resAddMenu(qintptr id_prop)
{
    Q_UNUSED(id_prop)
    return nullptr;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ информационные сообщения ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Выводит строку text в окно Отладка цветом color
//ru Всего возвращает 0.
EXPORT int _Debug(const char *text, int color)
{
    Q_UNUSED(color)

    qDebug("%s", text);
    return 0;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ среда ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru На основе индекса параметра, записываем данные в память value
EXPORT int GetParam(CgtParams index, void *value)
{
    m_model->getCgtParam(index, value);
    return 0;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ массив ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Получаем количество элементов в массиве.
EXPORT int arrCount(qintptr id_array)
{
    const PValue v = m_model->getValueById(id_array);
    if (!v)
        return 0;

    return v->getArraySize();
}

//ru Получаем тип элементов в массиве.
EXPORT DataType arrType(qintptr id_array)
{
    const PValue v = m_model->getValueById(id_array);
    if (!v)
        return data_null;

    return v->getSubType();
}

//ru Получаем имя элемента по индексу.
EXPORT const char *arrItemName(qintptr id_array, int index)
{
    const PValue v = m_model->getValueById(id_array);
    if (!v)
        return nullptr;

    return fcgt::strToCString(v->getArrayItemName(index));
}

//ru Получаем элемент (id_arrayValue) массива  по индексу.
//[deprecated]
EXPORT qintptr arrItemData(qintptr id_array, int index)
{
    Q_UNUSED(id_array)
    Q_UNUSED(index)
    return 0;
}

//ru Получаем элемент массива в виде свойства (id_prop) Оо,
//ru для дальнейшей работы с ним cgt::prop* функциями.
EXPORT qintptr arrGetItem(qintptr id_array, int index)
{
    const PValue v = m_model->getValueById(id_array);
    if (!v)
        return 0;

    const PValue arrValue = v->getArrayItemByIndex(index);
    if (arrValue) {
        delete m_model->getPropertyById(1);

        PProperty prop = new Property(1, arrValue->getType(), arrValue->getValue(), arrValue->getName());
        m_model->addPropertyToMap(prop);

        return 1;
    }

    return 0;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ среда ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращаем >0, если запускаем схемы в режиме отладки,
//ru иначе 0.
EXPORT int isDebug(qintptr id_element)
{
    Q_UNUSED(id_element)
    return m_model->getIsDebug();
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ работа с данными ~~~~~~~~~~~~~~~~~~~~~~~~~~

//ru Возвращает тип данных.
EXPORT DataType dtType(qintptr id_value)
{
    const PValue v = m_model->getValueById(id_value);
    if (!v)
        return data_null;

    return v->getDataType();
}

//ru Возвращает данные в формате: строка в стиле C.
EXPORT const char *dtStr(qintptr id_value)
{
    const PValue v = m_model->getValueById(id_value);
    if (!v)
        return nullptr;

    return fcgt::strToCString(v->toString());
}

//ru Возвращает данные в формате: целое число.
EXPORT int dtInt(qintptr id_value)
{
    const PValue v = m_model->getValueById(id_value);
    if (!v)
        return 0;

    return v->toInt();
}

//ru Возвращает данные в формате: число с плавающей запятой.
EXPORT qreal dtReal(qintptr id_value)
{
    const PValue v = m_model->getValueById(id_value);
    if (!v)
        return 0.0;

    return v->toReal();
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ шрифт ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает название шрифта.
EXPORT const char *fntName(qintptr id_font)
{
    PValue v = m_model->getValueById(id_font);
    if (!v)
        return nullptr;

    PValueFont font = v->toFont();
    if (!font)
        return nullptr;

    return fcgt::strToCString(font->name);
}
//ru Возвращает размер шрифта.
EXPORT int fntSize(qintptr id_font)
{
    PValue v = m_model->getValueById(id_font);
    if (!v)
        return 0;

    PValueFont font = v->toFont();
    if (!font)
        return 0;

    return font->size;
}
//ru Возвращает стиль шрифта.
EXPORT uchar fntStyle(qintptr id_font)
{
    PValue v = m_model->getValueById(id_font);
    if (!v)
        return 0;

    PValueFont font = v->toFont();
    if (!font)
        return 0;

    return font->style;
}
//ru Возвращает цвет шрифта.
EXPORT uint fntColor(qintptr id_font)
{
    PValue v = m_model->getValueById(id_font);
    if (!v)
        return 0;

    PValueFont font = v->toFont();
    if (!font)
        return 0;

    return font->color;
}
//ru Возвращает кодировку шрифта.
EXPORT uchar fntCharSet(qintptr id_font)
{
    PValue v = m_model->getValueById(id_font);
    if (!v)
        return 0;

    PValueFont font = v->toFont();
    if (!font)
        return 0;

    return font->charset;
}

//!~~~~~~~~~~~~~~~~элемент | пользовательские данные ~~~~~~~~~~~~~
//!ru Судя по CodeGen.dpr, используется для хранения указателя (ID элемента) на самого себя.

//ru Возвращает пользовательские данные элемента.
//ru Коммент из hiasm5 - user data used in FTCG codegen.
//ru Судя по всему, данные могут быть любого типа, ибо хранит указатель..
//ru Так же, скорее всего используется для хранения ID элемента
EXPORT qintptr elGetData(qintptr id_element)
{
    PElement e = m_model->getElementById(id_element);
    if (!e)
        return 0;

    return e->getUserData();
}

//ru Устанавливает пользовательские данные элементу.
//ru Коммент из hiasm5 - user data used in FTCG codegen.
//ru Судя по всему, данные могут быть любого типа, ибо хранит указатель.
//ru Так же, скорее всего используется для хранения ID элемента
EXPORT void elSetData(qintptr id_element, qintptr data)
{
    PElement e = m_model->getElementById(id_element);
    if (e)
        e->setUserData(data);
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ точки элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает тип данных точки.
EXPORT DataType ptGetDataType(qintptr id_point)
{
    const PPoint p = m_model->getPointById(id_point);
    if (!p)
        return data_null;

    return p->getDataType();
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ элемент ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает ID родительского контейнера элемента.
EXPORT qintptr elGetParent(qintptr id_element)
{
    const PElement e = m_model->getElementById(id_element);
    if (!e)
        return 0;

    const PContainer c = e->getParent();
    if (!c)
        return 0;

    return c->getId();
}

//ru Возвращает количество свойств в списке свойств(из панели свойств).
//[deprecated]
EXPORT int elGetPropertyListCount(qintptr id_element)
{
    Q_UNUSED(id_element)

    return 0;
}

//ru Возвращает свойство из списка свойств (PropertyList).
//[deprecated]
EXPORT qintptr elGetPropertyListItem(qintptr id_element, int index)
{
    Q_UNUSED(id_element)
    Q_UNUSED(index)

    return 0;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ список свойств элемента ~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает имя свойства.
//[deprecated]
EXPORT const char *plGetName(qintptr id_prop)
{
    Q_UNUSED(id_prop)
    return nullptr;
}

//ru Возвращает описание свойства.
//[deprecated]
EXPORT const char *plGetInfo(qintptr id_prop)
{
    Q_UNUSED(id_prop)
    return nullptr;
}

//ru Возвращает группу свойсва.
//[deprecated]
EXPORT const char *plGetGroup(qintptr id_prop)
{
    Q_UNUSED(id_prop)
    return nullptr;
}

//ru Возвращает указатель на данные свойства.
//[deprecated]
EXPORT qintptr plGetProperty(qintptr id_prop)
{
    Q_UNUSED(id_prop)
    return 0;
}

//ru Возвращает ID родительского элемента указанного свойства.
//[deprecated]
EXPORT qintptr plGetOwner(qintptr id_prop)
{
    Q_UNUSED(id_prop)
    return 0;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ точки элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает описание точки.
//[deprecated]
EXPORT const char *ptGetInfo(qintptr id_point)
{
    const PPoint p = m_model->getPointById(id_point);
    if (!p)
        return nullptr;

    return fcgt::strToCString(p->getInfo());
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ свойства элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает ID элемента, прилинкованного к указанному свойству.
EXPORT qintptr propGetLinkedElement(qintptr id_element, const char *propName)
{
    const PElement e = m_model->getElementById(id_element);
    if (!e)
        return 0;

    PProperty p = e->getPropertyByName(QString::fromLocal8Bit(propName));
    if (!p)
        return 0;

    const PLinkedElementInfo info = p->toLinkedElementInfo();
    if (!info)
        return 0;

    return info->id;
}

//ru Возвращает 1, если свойство помечено на перевод.
//[deprecated]
EXPORT int propIsTranslate(qintptr id_element, qintptr id_prop)
{
    Q_UNUSED(id_element)
    Q_UNUSED(id_prop)
    return 0;
}

/*
     * Возвращает ID элемента, прилинкованного к указанному свойству.
     * В буфер buf пишется имя интерфейса элемента.
     * Например в строке из INI: FormFastening=Форма для привязки позиции|20|(empty)|ControlManager
     * ControlManager - является той самой информацией передаваемой нам в buf.
     */
EXPORT qintptr propGetLinkedElementInfo(qintptr id_element, qintptr id_prop, char *buf)
{
    const PElement e = m_model->getElementById(id_element);
    if (!e)
        return 0;

    PProperty p = e->getPropertyById(id_prop);
    if (!p)
        return 0;

    const PLinkedElementInfo info = p->toLinkedElementInfo();
    if (!info)
        return 0;

    strcpy(buf, info->interface.toStdString().c_str());
    return info->id;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ элемент - CI_PolyMulti ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает id_sdk контейнера по его индексу из элемента.
EXPORT qintptr elGetSDKByIndex(qintptr id_element, int index)
{
    const PElement e = m_model->getElementById(id_element);
    if (!e)
        return 0;

    return e->getIdContainerByIndex(index);
}

//ru Возвращает количаство контейнеров полиморфного элемента(CI_PolyMulti).
EXPORT int elGetSDKCount(qintptr id_element)
{
    const PElement e = m_model->getElementById(id_element);
    if (!e)
        return 0;

    return e->getCountContainers();
}

//ru Возвращает имя контейнера по индексу.
EXPORT const char *elGetSDKName(qintptr id_element, int index)
{
    const PElement e = m_model->getElementById(id_element);
    if (!e)
        return nullptr;

    const PContainer c = e->getContainerByIndex(index);
    if (!c)
        return nullptr;

    return fcgt::strToCString(c->getName());
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ схема ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает элемент родитель для данного SDK.
//ru Возвращает 0, если контейнер не имеет родителя.
EXPORT qintptr sdkGetParent(qintptr id_sdk)
{
    const PContainer c = m_model->getContainerById(id_sdk);
    if (!c)
        return 0;

    PElement e = c->getParent();
    if (!e)
        return 0;

    return e->getId();
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ элемент ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает интерфейсы, предоставляемые элементом.
//ru Содержимое поля Interfaces= из конфигурации элемента.
EXPORT const char *elGetInterface(qintptr id_element)
{
    const PElement e = m_model->getElementById(id_element);
    if (!e)
        return nullptr;

    return fcgt::strToCString(e->getInterface());
}

//ru Возвращает список классов, от которых наследуется элемент
//ru Содержимое поля Inherit= из конфигурации элемента.
EXPORT const char *elGetInherit(qintptr id_element)
{
    const PElement e = m_model->getElementById(id_element);
    if (!e)
        return nullptr;

    return fcgt::strToCString(e->getInherit());
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ ресурсы ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает 1, если список ресурсов пуст, и 0 в противном случае.
EXPORT int resEmpty()
{
    return m_model->resIsEmpty();
}

//ru Устанавливает префикс для имен ресурсов.
//[deprecated]
EXPORT int resSetPref(const char *pref)
{
    Q_UNUSED(pref)
    return 0;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ информационные сообщения ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Добавляет информацию в информационную панель
EXPORT int _Error(int line, qintptr id_element, const char *text)
{
    Q_UNUSED(line)
    Q_UNUSED(id_element)
    Q_UNUSED(text)
    return 0;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ элемент ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает ID группы, к которой принадлежит элемент и 0, если группа отсутствует
//[deprecated]
EXPORT int elGetGroup(qintptr id_element)
{
    Q_UNUSED(id_element)
    return 0;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ свойства элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Сохраняет данные свойства в файл.
//[deprecated]
EXPORT int propSaveToFile(qintptr id_prop, const char *fileName)
{
    Q_UNUSED(id_prop)
    Q_UNUSED(fileName)

    return 0;
}

//Заполняем массив указателей
static qintptr emulateCgt[]{
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
//Сохранение указателя для дальнейшей работы с оным
void setSceneModel(SceneModel *collector)
{
    m_model = collector;
}

//Получаем массив указателей на функции
PCodeGenTools getCgt()
{
    return reinterpret_cast<PCodeGenTools>(emulateCgt);
}
}
