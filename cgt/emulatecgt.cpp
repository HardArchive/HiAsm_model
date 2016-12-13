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

#define EXPORT __stdcall

//ru Храним указатель на модель данных
static SceneModel *m_model = nullptr;

//~~~~~~~~~~~~~~~~~ Проксированные функции ~~~~~~~~~~~~~~~~~~~

//!~~~~~~~~~~~~~~~~~~~~~~~~ контейнер ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает количество элементов в контейнере.
static qint32 EXPORT sdkGetCount(qint32 id_sdk)
{
    return m_model->getCountElementsInContainer(id_sdk);
}

//ru Возвращает ID элемента по его Z-положению(индексу) в контейнере.
static qint32 EXPORT sdkGetElement(qint32 id_sdk, qint32 index)
{
    return m_model->getIdElementFromSDKByIndex(id_sdk, index);
}

//ru Возвращает ID элемента по имени элемента.
static qint32 EXPORT sdkGetElementName(qint32 id_sdk, char *name)
{
    const Container *c = m_model->getContainerById(id_sdk);
    if (!c)
        return 0;

    return c->getIdElementByName(QString::fromLocal8Bit(name));
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ элемент ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает флаги элемента.
static ElementFlags EXPORT elGetFlag(qint32 id_element)
{
    const Element *e = m_model->getElementById(id_element);
    if (!e)
        return ELEMENT_FLG_IS_FREEZE;

    return e->getFlags();
}

//ru Возвращает количество свойств элемента.
static qint32 EXPORT elGetPropCount(qint32 id_element)
{
    const Element *e = m_model->getElementById(id_element);
    if (!e)
        return 0;

    return e->getCountProps();
}

//ru Возвращает id свойства элемента по индексу, с порядковым номером из INI.
static Property EXPORT *elGetProperty(qint32 id_element, qint32 index)
{
    const Element *e = m_model->getElementById(id_element);
    if (!e)
        return nullptr;

    return e->getIdPropertyByIndex(index);
}

//ru Возвращает True, если значение свойства совпадает с заданным в INI файле, иначе False.
static bool EXPORT elIsDefProp(qint32 id_element, qint32 index)
{
    const Element *e = m_model->getElementById(id_element);
    if (!e)
        return false;

    Property *p = e->getPropertyByIndex(index);
    if (!p)
        return false;

    return p->getIsDefProp();
}

//ru Присваиваем элементу уникальное имя и возвращаем ID этого элемента.
static qint32 EXPORT elSetCodeName(qint32 id_element, const char *name)
{
    Element *e = m_model->getElementById(id_element);
    if (!e)
        return 0;

    e->setCodeName(QString::fromLocal8Bit(name));
    return id_element;
}

//ru Возвращает уникальное имя элемента
static const char *EXPORT elGetCodeName(qint32 id_element)
{
    const Element *e = m_model->getElementById(id_element);
    if (!e)
        return nullptr;

    return fcgt::strToCString(e->getCodeName());
}

//ru Возвращает имя класса элемента
static const char *EXPORT elGetClassName(qint32 id_element)
{
    const Element *e = m_model->getElementById(id_element);
    if (!e)
        return nullptr;

    return fcgt::strToCString(e->getClassName());
}

//ru Возвращает водержимое поля Sub из конфигурационного INI-файла элемента.
static const char *EXPORT elGetInfSub(qint32 id_element)
{
    const Element *e = m_model->getElementById(id_element);
    if (!e)
        return 0;

    return fcgt::strToCString(e->getInfSub());
}

//ru Возвращает общее количество видимых точек у элемента.
static qint32 EXPORT elGetPtCount(qint32 id_element)
{
    const Element *e = m_model->getElementById(id_element);
    if (!e)
        return 0;

    return e->getCountPoints();
}

//ru Возвращает ID точки по её индексу.
static Point *EXPORT elGetPt(qint32 id_element, qint32 index)
{
    const Element *e = m_model->getElementById(id_element);
    if (!e)
        return nullptr;

    return e->getIdPointByIndex(index);
}

//ru Возвращает ID точки по её имени.
static Point *EXPORT elGetPtName(qint32 id_element, const char *name)
{
    const Element *e = m_model->getElementById(id_element);
    if (!e)
        return nullptr;

    return e->getIdPointByName(QString::fromLocal8Bit(name));
}

//ru Возвращает индекс класса элемента.
static ElementClass EXPORT elGetClassIndex(qint32 id_element)
{
    Element *e = m_model->getElementById(id_element);
    if (!e)
        return CI_Element;

    return e->getClassIndex();
}

//ru Получаем ID контейнера из элемента.
//ru Если элемент не содержит контейнеры, возвращаем ID элемента родителя текущего контейнера.
static qint32 EXPORT elGetSDK(qint32 id_element)
{
    const Element *e = m_model->getElementById(id_element);
    if (!e)
        return 0;

    const Container *c = e->getContainer();
    if (c)
        return c->getId();

    const Element *p = qobject_cast<Element *>(e->parent()->parent());
    if (p) {
        return p->getId();
    }

    return 0;
}

//ru Возвращает True, если данный элемент является ссылкой, либо на него ссылаются.
static bool EXPORT elLinkIs(qint32 id_element)
{
    const Element *e = m_model->getElementById(id_element);
    if (!e)
        return false;

    return e->getLinkIs();
}

//ru Возвращает ID главного элемента(тот, на который ссылаются другие).
static qint32 EXPORT elLinkMain(qint32 id_element)
{
    const Element *e = m_model->getElementById(id_element);
    if (!e)
        return 0;

    return e->getLinkIs();
}

//ru Помещает в переменные "X" и "Y", позицию элемента в редакторе схем.
static void EXPORT elGetPos(qint32 id_element, qint32 &X, qint32 &Y)
{
    const Element *e = m_model->getElementById(id_element);
    if (!e)
        return;

    X = e->getPosX();
    Y = e->getPosY();
}

//ru Помещает в переменные "w" и "h", размеры элемента.
static void EXPORT elGetSize(qint32 id_element, qint32 &W, qint32 &H)
{
    const Element *e = m_model->getElementById(id_element);
    if (!e)
        return;

    W = e->getSizeW();
    H = e->getSizeH();
}

//ru Возвращает внутренний ID элемента (отличается от внешнего).
//[deprecated]
static qint32 EXPORT elGetEID(qint32 id_element)
{
    Q_UNUSED(id_element)
    return 0;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ точки элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Получаем ID точки с которой соединена указанная.
static Point *EXPORT ptGetLinkPoint(Point *id_point)
{
    if (!id_point)
        return nullptr;

    return id_point->getLinkPoint();
}

//ru Получаем ID точки с которой соединена указанная,
//ru без учета точек разрыва и хабов.
static Point *EXPORT ptGetRLinkPoint(Point *id_point)
{
    Q_CHECK_PTR(id_point);

    return id_point->getRLinkPoint();
}

//ru Получаем тип точки.
static PointType EXPORT ptGetType(Point *id_point)
{
    Q_CHECK_PTR(id_point);
    return id_point->getType();
}

//ru Возвращает имя точки.
static const char *EXPORT ptGetName(Point *id_point)
{
    if (!id_point)
        return nullptr;

    return fcgt::strToCString(id_point->getName());
}

//ru Получаем ID родителя (элемент) точки.
static qint32 EXPORT ptGetParent(Point *id_point)
{
    if (!id_point)
        return 0;

    const Element *e = qobject_cast<Element *>(id_point->parent());

    return e->getId();
}

//ru Получаем индекс точки относительно точек того же типа.
static qint32 EXPORT ptGetIndex(Point *id_point)
{
    if (!id_point)
        return 0;

    return id_point->getIndex();
}

//ru Возвращает базовую часть имени динамической точки(для CI_DPElement).
static const char *EXPORT pt_dpeGetName(Point *id_point)
{
    if (!id_point)
        return nullptr;

    return fcgt::strToCString(id_point->getDpeName());
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ свойства элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает тип свойства.
static DataType EXPORT propGetType(Property *prop)
{
    if (!prop)
        return data_null;

    return prop->getType();
}

//ru Возвращает имя свойства.
static const char *EXPORT propGetName(Property *prop)
{
    if (!prop)
        return nullptr;

    return fcgt::strToCString(prop->getName());
}

//ru Возвращает значение свойства в виде указателя на данные.
static Value *EXPORT propGetValue(Property *prop)
{
    if (!prop)
        return nullptr;

    Value *v = prop->getValue();
    if (!v)
        return nullptr;

    return v;
}

//ru Возвращает значение свойства в формате uchar.
static uchar EXPORT propToByte(Property *prop)
{
    if (!prop)
        return 0;

    return prop->toByte();
}

//ru Возвращает значение свойства в формате qint32.
static qint32 EXPORT propToInteger(Property *prop)
{
    if (!prop)
        return 0;

    return prop->toInt();
}

//ru Возвращает значение свойства в формате float.
static qreal EXPORT propToReal(Property *prop)
{
    if (!prop)
        return 0;

    return prop->toReal();
}

//ru Возвращает значение свойства в виде C строки.
static const char *EXPORT propToString(Property *prop)
{
    if (!prop)
        return 0;

    return fcgt::strToCString(prop->toString());
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ ресурсы ~~~~~~~~~~~~~~~~~~~~~~~~~~

//ru Добавляет имя файла в список временных файлов
//ru для последующего удаления файла.
static qint32 EXPORT resAddFile(const char *filePath)
{
    return m_model->addResList(QString::fromLocal8Bit(filePath));
}

//ru Добавляет иконку в ресурсы и в список временных файлов,
//ru и возвращают имя временного файла.
static const char *EXPORT resAddIcon(Property *id_prop)
{
    return m_model->addStreamRes(id_prop);
}

//ru Добавляет строку в ресурсы и в список временных файлов.
//ru Возвращают имя временного файла.
static const char *EXPORT resAddStr(const char *string)
{
    return m_model->addStringRes(QString::fromLocal8Bit(string));
}

//ru Добавляет поток (данные) в ресурсы и в список временных файлов,
//ru и возвращает имя временного файла.
//ru Временный файл создаётся в папке %HiAsm%\compiler и существует до конца
//ru работы с библиотекой.
static const char *EXPORT resAddStream(Property *id_prop)
{
    return m_model->addStreamRes(id_prop);
}

//ru Добавляет звук в ресурсы и в список временных файлов,
//ru и возвращает имя временного файла.
//ru Временный файл создаётся в папке %HiAsm%\compiler и существует до конца
//ru работы с библиотекой.
static const char *EXPORT resAddWave(Property *id_prop)
{
    return m_model->addStreamRes(id_prop);
}

//ru Добавляет картинку в ресурсы и в список временных файлов,
//ru и возвращает имя временного файла.
//ru Временный файл создаётся в папке %HiAsm%\compiler и существует до конца
//ru работы с библиотекой.
static const char *EXPORT resAddBitmap(Property *id_prop)
{
    return m_model->addStreamRes(id_prop);
}

//ru Добавляет меню в ресурсы и в список временных файлов.
//[deprecated]
static const char *EXPORT resAddMenu(qint32 id_prop)
{
    Q_UNUSED(id_prop)
    return nullptr;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ информационные сообщения ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Выводит строку text в окно Отладка цветом color
//ru Всего возвращает 0.
static qint32 EXPORT _Debug(const char *text, qint32 color)
{
    Q_UNUSED(color)

    qDebug("%s", text);
    return 0;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ среда ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru На основе индекса параметра, записываем данные в память value
static qint32 EXPORT GetParam(CgtParams index, void *value)
{
    m_model->getCgtParam(index, value);
    return 0;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ массив ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Получаем количество элементов в массиве.
static qint32 EXPORT arrCount(Value *id_array)
{
    if (!id_array)
        return 0;

    return id_array->getArraySize();
}

//ru Получаем тип элементов в массиве.
static DataType EXPORT arrType(Value *id_array)
{
    if (!id_array)
        return data_null;

    return id_array->getSubType();
}

//ru Получаем имя элемента по индексу.
static const char *EXPORT arrItemName(Value *id_array, qint32 index)
{
    if (!id_array)
        return nullptr;

    return fcgt::strToCString(id_array->getArrayItemName(index));
}

//ru Получаем элемент (id_arrayValue) массива  по индексу.
//[deprecated]
static qint32 EXPORT arrItemData(qint32 id_array, qint32 index)
{
    Q_UNUSED(id_array)
    Q_UNUSED(index)
    return 0;
}

//ru Получаем элемент массива в виде свойства (id_prop) Оо,
//ru для дальнейшей работы с ним cgt::prop* функциями.
//TODO Утечка
static Property *EXPORT arrGetItem(Value *array, qint32 index)
{
    if (!array)
        return nullptr;

    const SharedValue arrValue = array->getArrayItemByIndex(index);
    if (arrValue) {
        Property *prop = new Property(arrValue->getType(), arrValue->getValue(), arrValue->getName());

        return prop;
    }

    return nullptr;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ среда ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращаем >0, если запускаем схемы в режиме отладки,
//ru иначе 0.
static qint32 EXPORT isDebug(qint32 id_element)
{
    Q_UNUSED(id_element)
    return m_model->getIsDebug();
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ работа с данными ~~~~~~~~~~~~~~~~~~~~~~~~~~

//ru Возвращает тип данных.
static DataType EXPORT dtType(Value *id_value)
{
    if (!id_value)
        return data_null;

    return id_value->getDataType();
}

//ru Возвращает данные в формате: строка в стиле C.
static const char *EXPORT dtStr(Value *id_value)
{
    if (!id_value)
        return nullptr;

    return fcgt::strToCString(id_value->toString());
}

//ru Возвращает данные в формате: целое число.
static qint32 EXPORT dtInt(Value *id_value)
{
    if (!id_value)
        return 0;

    return id_value->toInt();
}

//ru Возвращает данные в формате: число с плавающей запятой.
static qreal EXPORT dtReal(Value *id_value)
{
    if (!id_value)
        return 0.0;

    return id_value->toReal();
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ шрифт ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает название шрифта.
static const char *EXPORT fntName(Value *id_font)
{
    if (!id_font)
        return nullptr;

    SharedValueFont font = id_font->toFont();
    if (!font)
        return nullptr;

    return fcgt::strToCString(font->name);
}
//ru Возвращает размер шрифта.
static qint32 EXPORT fntSize(Value *id_font)
{
    if (!id_font)
        return 0;

    SharedValueFont font = id_font->toFont();
    if (!font)
        return 0;

    return font->size;
}
//ru Возвращает стиль шрифта.
static uchar EXPORT fntStyle(Value *id_font)
{
    if (!id_font)
        return 0;

    SharedValueFont font = id_font->toFont();
    if (!font)
        return 0;

    return font->style;
}
//ru Возвращает цвет шрифта.
static qint32 EXPORT fntColor(Value *id_font)
{
    if (!id_font)
        return 0;

    SharedValueFont font = id_font->toFont();
    if (!font)
        return 0;

    return font->color;
}
//ru Возвращает кодировку шрифта.
static uchar EXPORT fntCharSet(Value *id_font)
{
    if (!id_font)
        return 0;

    SharedValueFont font = id_font->toFont();
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
static qint32 EXPORT elGetData(qint32 id_element)
{
    Element *e = m_model->getElementById(id_element);
    if (!e)
        return 0;

    return e->getUserData();
}

//ru Устанавливает пользовательские данные элементу.
//ru Коммент из hiasm5 - user data used in FTCG codegen.
//ru Судя по всему, данные могут быть любого типа, ибо хранит указатель.
//ru Так же, скорее всего используется для хранения ID элемента
static void EXPORT elSetData(qint32 id_element, qint32 data)
{
    Element *e = m_model->getElementById(id_element);
    if (e)
        e->setUserData(data);
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ точки элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает тип данных точки.
static DataType EXPORT ptGetDataType(Point *id_point)
{
    if (!id_point)
        return data_null;

    return id_point->getDataType();
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ элемент ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает ID родительского контейнера элемента.
static qint32 EXPORT elGetParent(qint32 id_element)
{
    const Element *e = m_model->getElementById(id_element);
    if (!e)
        return 0;

    const Container *c = e->getParent();
    if (!c)
        return 0;

    return c->getId();
}

//ru Возвращает количество свойств в списке свойств(из панели свойств).
//[deprecated]
static qint32 EXPORT elGetPropertyListCount(qint32 id_element)
{
    Q_UNUSED(id_element)

    return 0;
}

//ru Возвращает свойство из списка свойств (PropertyList).
//[deprecated]
static qint32 EXPORT elGetPropertyListItem(qint32 id_element, qint32 index)
{
    Q_UNUSED(id_element)
    Q_UNUSED(index)

    return 0;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ список свойств элемента ~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает имя свойства.
//[deprecated]
static const char *EXPORT plGetName(qint32 id_prop)
{
    Q_UNUSED(id_prop)
    return nullptr;
}

//ru Возвращает описание свойства.
//[deprecated]
static const char *EXPORT plGetInfo(qint32 id_prop)
{
    Q_UNUSED(id_prop)
    return nullptr;
}

//ru Возвращает группу свойсва.
//[deprecated]
static const char *EXPORT plGetGroup(qint32 id_prop)
{
    Q_UNUSED(id_prop)
    return nullptr;
}

//ru Возвращает указатель на данные свойства.
//[deprecated]
static qint32 EXPORT plGetProperty(qint32 id_prop)
{
    Q_UNUSED(id_prop)
    return 0;
}

//ru Возвращает ID родительского элемента указанного свойства.
//[deprecated]
static qint32 EXPORT plGetOwner(qint32 id_prop)
{
    Q_UNUSED(id_prop)
    return 0;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ точки элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает описание точки.
//[deprecated]
static const char *EXPORT ptGetInfo(Point *id_point)
{
    if (!id_point)
        return nullptr;

    return fcgt::strToCString(id_point->getInfo());
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ свойства элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает ID элемента, прилинкованного к указанному свойству.
static qint32 EXPORT propGetLinkedElement(qint32 id_element, const char *propName)
{
    const Element *e = m_model->getElementById(id_element);
    if (!e)
        return 0;

    Property *p = e->getPropertyByName(QString::fromLocal8Bit(propName));
    if (!p)
        return 0;

    const SharedLinkedElementInfo info = p->toLinkedElementInfo();
    if (!info)
        return 0;

    return info->id;
}

//ru Возвращает 1, если свойство помечено на перевод.
//[deprecated]
static qint32 EXPORT propIsTranslate(qint32 id_element, qint32 id_prop)
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
static qint32 EXPORT propGetLinkedElementInfo(qint32 id_element, Property *id_prop, char *buf)
{
    const Element *e = m_model->getElementById(id_element);
    if (!e)
        return 0;

    Property *p = e->getPropertyById(id_prop);
    if (!p)
        return 0;

    const SharedLinkedElementInfo info = p->toLinkedElementInfo();
    if (!info)
        return 0;

    strcpy(buf, info->interface.toStdString().c_str());
    return info->id;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ элемент - CI_PolyMulti ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает id_sdk контейнера по его индексу из элемента.
static qint32 EXPORT elGetSDKByIndex(qint32 id_element, qint32 index)
{
    const Element *e = m_model->getElementById(id_element);
    if (!e)
        return 0;

    return e->getIdContainerByIndex(index);
}

//ru Возвращает количаство контейнеров полиморфного элемента(CI_PolyMulti).
static qint32 EXPORT elGetSDKCount(qint32 id_element)
{
    const Element *e = m_model->getElementById(id_element);
    if (!e)
        return 0;

    return e->getCountContainers();
}

//ru Возвращает имя контейнера по индексу.
static const char *EXPORT elGetSDKName(qint32 id_element, qint32 index)
{
    const Element *e = m_model->getElementById(id_element);
    if (!e)
        return nullptr;

    const Container *c = e->getContainerByIndex(index);
    if (!c)
        return nullptr;

    return fcgt::strToCString(c->getName());
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ схема ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает элемент родитель для данного SDK.
//ru Возвращает 0, если контейнер не имеет родителя.
static qint32 EXPORT sdkGetParent(qint32 id_sdk)
{
    const Container *c = m_model->getContainerById(id_sdk);
    Q_CHECK_PTR(c);

    Element *e = c->getParent();
    if (!e)
        return 0;

    return e->getId();
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ элемент ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает интерфейсы, предоставляемые элементом.
//ru Содержимое поля Interfaces= из конфигурации элемента.
static const char *EXPORT elGetInterface(qint32 id_element)
{
    const Element *e = m_model->getElementById(id_element);
    if (!e)
        return nullptr;

    return fcgt::strToCString(e->getInterface());
}

//ru Возвращает список классов, от которых наследуется элемент
//ru Содержимое поля Inherit= из конфигурации элемента.
static const char *EXPORT elGetInherit(qint32 id_element)
{
    const Element *e = m_model->getElementById(id_element);
    if (!e)
        return nullptr;

    return fcgt::strToCString(e->getInherit());
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ ресурсы ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает 1, если список ресурсов пуст, и 0 в противном случае.
static qint32 EXPORT resEmpty()
{
    return m_model->resIsEmpty();
}

//ru Устанавливает префикс для имен ресурсов.
//[deprecated]
static qint32 EXPORT resSetPref(const char *pref)
{
    Q_UNUSED(pref)
    return 0;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ информационные сообщения ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Добавляет информацию в информационную панель
static qint32 EXPORT _Error(qint32 line, qint32 id_element, const char *text)
{
    Q_UNUSED(line)
    Q_UNUSED(id_element)
    Q_UNUSED(text)
    return 0;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ элемент ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Возвращает ID группы, к которой принадлежит элемент и 0, если группа отсутствует
//[deprecated]
static qint32 EXPORT elGetGroup(qint32 id_element)
{
    Q_UNUSED(id_element)
    return 0;
}

//!~~~~~~~~~~~~~~~~~~~~~~~~ свойства элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
//ru Сохраняет данные свойства в файл.
//[deprecated]
static qint32 EXPORT propSaveToFile(Property *id_prop, const char *fileName)
{
    Q_UNUSED(id_prop)
    Q_UNUSED(fileName)

    return 0;
}

//Заполняем массив указателей
static void *emulateCgt[]{
    reinterpret_cast<void *>(sdkGetCount),
    reinterpret_cast<void *>(sdkGetElement),
    reinterpret_cast<void *>(sdkGetElementName),
    reinterpret_cast<void *>(elGetFlag),
    reinterpret_cast<void *>(elGetPropCount),
    reinterpret_cast<void *>(elGetProperty),
    reinterpret_cast<void *>(elIsDefProp),
    reinterpret_cast<void *>(elSetCodeName),
    reinterpret_cast<void *>(elGetCodeName),
    reinterpret_cast<void *>(elGetClassName),
    reinterpret_cast<void *>(elGetInfSub),
    reinterpret_cast<void *>(elGetPtCount),
    reinterpret_cast<void *>(elGetPt),
    reinterpret_cast<void *>(elGetPtName),
    reinterpret_cast<void *>(elGetClassIndex),
    reinterpret_cast<void *>(elGetSDK),
    reinterpret_cast<void *>(elLinkIs),
    reinterpret_cast<void *>(elLinkMain),
    reinterpret_cast<void *>(elGetPos),
    reinterpret_cast<void *>(elGetSize),
    reinterpret_cast<void *>(elGetEID),
    reinterpret_cast<void *>(ptGetLinkPoint),
    reinterpret_cast<void *>(ptGetRLinkPoint),
    reinterpret_cast<void *>(ptGetType),
    reinterpret_cast<void *>(ptGetName),
    reinterpret_cast<void *>(ptGetParent),
    reinterpret_cast<void *>(ptGetIndex),
    reinterpret_cast<void *>(pt_dpeGetName),
    reinterpret_cast<void *>(propGetType),
    reinterpret_cast<void *>(propGetName),
    reinterpret_cast<void *>(propGetValue),
    reinterpret_cast<void *>(propToByte),
    reinterpret_cast<void *>(propToInteger),
    reinterpret_cast<void *>(propToReal),
    reinterpret_cast<void *>(propToString),
    reinterpret_cast<void *>(resAddFile),
    reinterpret_cast<void *>(resAddIcon),
    reinterpret_cast<void *>(resAddStr),
    reinterpret_cast<void *>(resAddStream),
    reinterpret_cast<void *>(resAddWave),
    reinterpret_cast<void *>(resAddBitmap),
    reinterpret_cast<void *>(resAddMenu),
    reinterpret_cast<void *>(_Debug),
    reinterpret_cast<void *>(GetParam),
    reinterpret_cast<void *>(arrCount),
    reinterpret_cast<void *>(arrType),
    reinterpret_cast<void *>(arrItemName),
    reinterpret_cast<void *>(arrItemData),
    reinterpret_cast<void *>(arrGetItem),
    reinterpret_cast<void *>(isDebug),
    reinterpret_cast<void *>(dtType),
    reinterpret_cast<void *>(dtStr),
    reinterpret_cast<void *>(dtInt),
    reinterpret_cast<void *>(dtReal),
    reinterpret_cast<void *>(fntName),
    reinterpret_cast<void *>(fntSize),
    reinterpret_cast<void *>(fntStyle),
    reinterpret_cast<void *>(fntColor),
    reinterpret_cast<void *>(fntCharSet),
    reinterpret_cast<void *>(elGetData),
    reinterpret_cast<void *>(elSetData),
    reinterpret_cast<void *>(ptGetDataType),
    reinterpret_cast<void *>(elGetParent),
    reinterpret_cast<void *>(elGetPropertyListCount),
    reinterpret_cast<void *>(elGetPropertyListItem),
    reinterpret_cast<void *>(plGetName),
    reinterpret_cast<void *>(plGetInfo),
    reinterpret_cast<void *>(plGetGroup),
    reinterpret_cast<void *>(plGetProperty),
    reinterpret_cast<void *>(plGetOwner),
    reinterpret_cast<void *>(ptGetInfo),
    reinterpret_cast<void *>(propGetLinkedElement),
    reinterpret_cast<void *>(propIsTranslate),
    reinterpret_cast<void *>(propGetLinkedElementInfo),
    reinterpret_cast<void *>(elGetSDKByIndex),
    reinterpret_cast<void *>(elGetSDKCount),
    reinterpret_cast<void *>(elGetSDKName),
    reinterpret_cast<void *>(sdkGetParent),
    reinterpret_cast<void *>(elGetInterface),
    reinterpret_cast<void *>(elGetInherit),
    reinterpret_cast<void *>(resEmpty),
    reinterpret_cast<void *>(resSetPref),
    reinterpret_cast<void *>(_Error),
    reinterpret_cast<void *>(elGetGroup),
    reinterpret_cast<void *>(propSaveToFile),
};

/*!  Служебные функции   */
//Сохранение указателя для дальнейшей работы с оным
void EmulateCgt::setSceneModel(SceneModel *model)
{
    m_model = model;
}

//Получаем массив указателей на функции
TCodeGenTools *EmulateCgt::getCgt()
{
    return reinterpret_cast<TCodeGenTools*>(emulateCgt);
}
