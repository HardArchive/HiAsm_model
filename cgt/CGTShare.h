#pragma once

//Project

//STL
#include <functional>

//Qt
#include <QtCore>
#include <QBitArray>

//!!! ========== Поддерживается только HiAsm 4, пакет Windows ==========

//!ru Флаги элемента
enum ElementFlags {
    //ru Элемент заморожен (нельзя перемещать).
    ELEMENT_FLG_IS_FREEZE = 0x0,

    //ru Элемент является частью интерфейса.
    ELEMENT_FLG_ONE_WIDGET = 0x1,

    //ru Элемент нельзя удалить.
    ELEMENT_FLG_IS_NODELETE = 0x2,

    //ru Элемент является редактором контейнера.
    //ru Например: EditMulti, EditMultiEx, EditPoliMulti.
    ELEMENT_FLG_IS_EDIT = 0x20,

    //ru Элемент является контейнером.
    ELEMENT_FLG_IS_MULTI = 0x40,

    //ru Элемент выбран в редакторе схем.
    ELEMENT_FLG_IS_SELECT = 0x100,

    //ru Родитель для элементов текущей SDK.
    ELEMENT_FLG_IS_PARENT = 0x200,

    //ru Элемент является базовым.
    //ru Например: CI_HubEx, CI_GetDataEx, ElementInfoTip, HCButton.
    ELEMENT_FLG_IS_CORE = 0x400,

    //ru Элемент является ссылкой, либо на него ссылаются.
    ELEMENT_FLG_IS_LINK = 0x800,
};
typedef QFlags<ElementFlags> ElementFlgs;

//!ru Типы точек
enum PointType {
    //ru Метод
    pt_Work = 1,

    //ru Событие
    pt_Event,

    //ru Переменная
    pt_Var,

    //ru Данные
    pt_Data
};
const static QMap<qint32, QString> PointTypeMap{
    {pt_Work, "pt_Work"},
    {pt_Event, "pt_Event"},
    {pt_Var, "pt_Var"},
    {pt_Data, "pt_Data"}};

//!ru Типы данных
enum DataType {
    data_null = 0,
    data_int,
    data_str,
    data_data,
    data_combo,
    data_list,
    data_icon,
    data_real,
    data_color,
    data_script,
    data_stream,
    data_bitmap,
    data_wave,
    data_array,
    data_comboEx,
    data_font,
    data_matr,
    data_jpeg,
    data_menu,
    data_code,
    data_element,
    data_flags,
    data_object
};
const static QMap<qint32, QString> DataTypeMap{
    {data_null, "data_null"},
    {data_int, "data_int"},
    {data_str, "data_str"},
    {data_data, "data_data"},
    {data_combo, "data_combo"},
    {data_list, "data_list"},
    {data_icon, "data_icon"},
    {data_real, "data_real"},
    {data_color, "data_color"},
    {data_script, "data_color"},
    {data_stream, "data_stream"},
    {data_bitmap, "data_bitmap"},
    {data_wave, "data_wave"},
    {data_array, "data_array"},
    {data_comboEx, "data_comboEx"},
    {data_font, "data_font"},
    {data_matr, "data_matr"},
    {data_jpeg, "data_jpeg"},
    {data_menu, "data_menu"},
    {data_code, "data_code"},
    {data_element, "data_element"},
    {data_flags, "data_flags"},
    {data_object, "data_object"}};

//!ru Классы элементов (elGetClassIndex)
enum ElementClass {
    //ru Просто элемент.
    CI_Element = 0,
    //ru Элемент с динамическими точками (автонумерация), например - IndexToChanel.
    //D - Dynamic, P - Point.
    CI_DPElement,
    //ru Контейнер
    CI_MultiElement,
    //ru Редактор контейнера MultiElement.
    CI_EditMulti,
    //ru Редактор динамического контейнера.
    CI_EditMultiEx,
    //ru Элемент для встраивания кода.
    CI_InlineCode,
    //ru Ручная отрисовка элемента интерфейса.
    CI_DrawElement,
    //ru Специальный класс, который используется для реализации ActionSkin.
    //ru Элемент AS_Control.
    CI_AS_Special,
    //ru Элемент со списком динамических точек.
    //ru Например элемент - VBScript.
    //D - Dynamic, P - Point, L - List
    CI_DPLElement,
    //ru Упрощённое подключение внешних библиотек.
    CI_UseHiDLL,
    //ru Элемент интерфейса, которым можно управлять в дизайнере форм.
    CI_WinElement,
    //ru Сноска.
    //ru PointHint - элемент базового пакета (_base).
    CI_PointHint,
    //ru Эмулятор элемента.
    //ru PointElement - элемент базового пакета (_base).
    CI_PointElement,
    //ru Разрыв линии.
    //ru LineBreak - элемент базового пакета (_base).
    CI_LineBreak,
    //ru Разрыв линии.
    //ru LineBreakEx - элемент базового пакета (_base).
    CI_LineBreakEx,
    //ru Пользовательский элемент.
    CI_UserElement,
    //ru Элемент для работы с переводом.
    //ru В пакете Windows, именуется как Class=Translator.
    CI_Translate,
    //ru Полиморфный контейнер.
    //ru Элемент может содержать более одного контейнера.
    CI_PolyMulti,
    //ru Шаблон документа.
    CI_DocumentTemplate
};
const static QMap<qint32, QString> ElementClassMap{
    {CI_Element, "CI_Element"},
    {CI_DPElement, "CI_DPElement"},
    {CI_MultiElement, "CI_MultiElement"},
    {CI_EditMulti, "CI_EditMulti"},
    {CI_EditMultiEx, "CI_EditMultiEx"},
    {CI_InlineCode, "CI_InlineCode"},
    {CI_DrawElement, "CI_DrawElement"},
    {CI_AS_Special, "CI_AS_Special"},
    {CI_DPLElement, "CI_DPLElement"},
    {CI_UseHiDLL, "CI_UseHiDLL"},
    {CI_WinElement, "CI_WinElement"},
    {CI_PointHint, "CI_PointHint"},
    {CI_PointElement, "CI_PointElement"},
    {CI_LineBreak, "CI_LineBreak"},
    {CI_LineBreakEx, "CI_LineBreakEx"},
    {CI_UserElement, "CI_UserElement"},
    {CI_Translate, "CI_Translate"},
    {CI_PolyMulti, "CI_PolyMulti"},
    {CI_DocumentTemplate, "CI_DocumentTemplate"}};

//!ru Индексы параметров среды - GetParam()
enum CgtParams {
    PARAM_CODE_PATH = 0,
    PARAM_DEBUG_MODE,
    PARAM_DEBUG_SERVER_PORT,
    PARAM_DEBUG_CLIENT_PORT,
    PARAM_PROJECT_PATH,
    PARAM_HIASM_VERSION,
    PARAM_USER_NAME,
    PARAM_USER_MAIL,
    PARAM_PROJECT_NAME,
    PARAM_SDE_WIDTH,
    PARAM_SDE_HEIGHT,
    PARAM_COMPILER
};
const static QMap<qint32, QString> CgtParamsMap{
    {PARAM_CODE_PATH, "PARAM_CODE_PATH"},
    {PARAM_DEBUG_MODE, "PARAM_DEBUG_MODE"},
    {PARAM_DEBUG_SERVER_PORT, "PARAM_DEBUG_SERVER_PORT"},
    {PARAM_DEBUG_CLIENT_PORT, "PARAM_DEBUG_CLIENT_PORT"},
    {PARAM_PROJECT_PATH, "PARAM_PROJECT_PATH"},
    {PARAM_HIASM_VERSION, "PARAM_HIASM_VERSION"},
    {PARAM_USER_NAME, "PARAM_USER_NAME"},
    {PARAM_USER_MAIL, "PARAM_USER_MAIL"},
    {PARAM_PROJECT_NAME, "PARAM_PROJECT_NAME"},
    {PARAM_SDE_WIDTH, "PARAM_SDE_WIDTH"},
    {PARAM_SDE_HEIGHT, "PARAM_SDE_HEIGHT"},
    {PARAM_COMPILER, "PARAM_COMPILER"}};

//!ru Ошибки при работе с библиотекой кодогенератора
enum CgResult {
    //ru Успешное завершение.
    CG_SUCCESS = 0,

    //ru Кодогенератор не найден.
    CG_NOT_FOUND = 1,

    //ru Используемая версия среды не поддерживается.
    CG_INVALID_VERSION = 2,

    //ru Точка входа в кодогенератор не найдена.
    CG_ENTRY_POINT_NF = 3,

    //ru Общая ошибка при сборке проекта.
    CG_BUILD_FAILED = 10,

    //ru Результат компиляции не найден.
    CG_APP_NOT_FOUND = 20
};
const static QMap<qint32, QString> CgResultMap{
    {CG_SUCCESS, "CG_SUCCESS"},
    {CG_NOT_FOUND, "CG_NOT_FOUND"},
    {CG_INVALID_VERSION, "CG_INVALID_VERSION"},
    {CG_ENTRY_POINT_NF, "CG_ENTRY_POINT_NF"},
    {CG_BUILD_FAILED, "CG_BUILD_FAILED"},
    {CG_APP_NOT_FOUND, "CG_APP_NOT_FOUND"}};

//!ru Параметры проекта
enum ProjectFlags {
    //ru Поддерживает сжатие.
    CGMP_COMPRESSED = 0x01,

    //ru Поддерживает запуск из среды.
    CGMP_RUN = 0x02,

    //ru Поддерживает запуск из среды в отладочном режиме.
    CGMP_RUN_DEBUG = 0x04,

    //ru Поддерживает внешний редактор форм.
    CGMP_FORM_EDIT = 0x08
};
typedef QFlags<ProjectFlags> ProjectFlgs;

/*
 * Описание интерфейса make_*
 *
*/

struct TBuildMakePrjRec {
    void *result;
    const char *prjFilename;
    const char *compiler;
};

struct TBuildCompliteRec {
    const char *prjFilename;
    const char *appFilename;
};

struct TBuildParams {
    qint32 flags;
};

struct TBuildRunRec {
    const char *FileName;
    qint32 Mode;
    qint32 ServerPort;
    qint32 ClientPort;
    void *data;
};

typedef qint32 (*TBuildCompliteProc)(const TBuildCompliteRec &params);
typedef qint32 (*TBuildGetParamsProc)(TBuildParams &params);
typedef qint32 (*TBuildMakePrj)(const TBuildMakePrjRec &params);
typedef qint32 (*TBuildRunProc)(TBuildRunRec &params);
typedef qint32 (*TBuildStopProc)(TBuildRunRec &params);

/*
 * Описание интерфейса библиотеки CodeGen.
 *
*/
struct THiAsmVersion {
    qint32 major{};
    qint32 minor{};
    qint32 build{};
};

struct TCodeGenTools;
struct TBuildProcessRec {
    TCodeGenTools *cgt{};
    qint32 sdk{};
    void *result{};
};

typedef CgResult (*TBuildPrepareProc)(void *params);
typedef CgResult (*TBuildProcessProc)(TBuildProcessRec &params);
typedef CgResult (*TCheckVersionProc)(const THiAsmVersion &params);

struct TCodeGenTools {
#define CALLBACK __stdcall

    //!~~~~~~~~~~~~~~~~~~~~~~~~ контейнер ~~~~~~~~~~~~~~~~~~~~~~~~~~

    //ru Возвращает количество элементов в контейнере.
    CALLBACK qint32 (*sdkGetCount)(qint32 SDK);
    //ru Возвращает ID элемента по его Z-положению(индексу) в контейнере.
    CALLBACK qint32 (*sdkGetElement)(qint32 SDK, qint32 Index);
    //ru Возвращает ID элемента по имени элемента.
    CALLBACK qint32 (*sdkGetElementName)(qint32 SDK, char *Name);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ элемент ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает флаги элемента.
    CALLBACK ElementFlags (*elGetFlag)(qint32 e);
    //ru Возвращает количество свойств элемента.
    CALLBACK qint32 (*elGetPropCount)(qint32 e);
    //ru Возвращает свойство элемента по индексу, с порядковым номером из INI.
    CALLBACK qint32 (*elGetProperty)(qint32 e, qint32 Index);
    //ru Возвращает True, если значение свойства совпадает с заданным в INI файле, иначе False.
    CALLBACK bool (*elIsDefProp)(qint32 e, qint32 Index);
    //ru Присваиваем элементу уникальное имя и возвращаем ID этого элемента.
    CALLBACK qint32 (*elSetCodeName)(qint32 e, const char *Name);
    //ru Возвращает уникальное имя элемента
    CALLBACK const char *(*elGetCodeName)(qint32 e);
    //ru Возвращает имя класса элемента.
    CALLBACK const char *(*elGetClassName)(qint32 e);
    //ru Возвращает водержимое поля Sub из конфигурационного INI-файла элемента.
    CALLBACK const char *(*elGetInfSub)(qint32 e);
    //ru Возвращает общее количество видимых точек у элемента.
    CALLBACK qint32 (*elGetPtCount)(qint32 e);
    //ru Возвращает ID точки по её индексу.
    CALLBACK qint32 (*elGetPt)(qint32 e, qint32 i);
    //ru Возвращает ID точки по её имени.
    //[deprecated]
    CALLBACK qint32 (*elGetPtName)(qint32 e, const char *Name);
    //ru Возвращает индекс класса элемента.
    CALLBACK ElementClass (*elGetClassIndex)(qint32 e);
    //ru Возвращает ID внутренней схемы для контейнеров
    //ru или ID родителя id_element для редактора контейнера (ELEMENT_FLG_IS_EDIT).
    CALLBACK qint32 (*elGetSDK)(qint32 e);
    //ru Возвращает True, если данный элемент является ссылкой, либо на него ссылаются.
    CALLBACK bool (*elLinkIs)(qint32 e);
    //ru Возвращает ID главного элемента(тот, на который ссылаются другие).
    CALLBACK qint32 (*elLinkMain)(qint32 e);
    //ru Помещает в переменные "X" и "Y", позицию элемента в редакторе схем.
    CALLBACK void (*elGetPos)(qint32 e, qint32 &X, qint32 &Y);
    //ru Помещает в переменные "W" и "H", размеры элемента
    CALLBACK void (*elGetSize)(qint32 e, qint32 &W, qint32 &H);
    //ru Возвращает внутренний ID элемента (отличается от внешнего).
    //[deprecated]
    CALLBACK qint32 (*elGetEID)(qint32 e);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ точки элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает ID точки, с которой соединена указанная.
    //TODO [deprecated?], в CodeGen.dpr не используется.
    CALLBACK qint32 (*ptGetLinkPoint)(qint32 p);
    //ru Возвращает ID точки, с которой соединена указанная точка,
    //ru без учета точек разрыва и хабов.
    CALLBACK qint32 (*ptGetRLinkPoint)(qint32 p);
    //ru Возвращает тип точек(константы PointTypes).
    CALLBACK PointType (*ptGetType)(qint32 p);
    //ru Возвращает имя точки.
    CALLBACK const char *(*ptGetName)(qint32 p);
    //ru Возвращает ID элемента, которому принадлежит точка.
    CALLBACK qint32 (*ptGetParent)(qint32 p);
    //ru Возвращает тип точки (PointTypes).
    CALLBACK qint32 (*ptGetIndex)(qint32 p);
    //ru Возвращает базовую часть имени динамической точки(для CI_DPElement).
    CALLBACK const char *(*pt_dpeGetName)(qint32 p);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ свойства элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает тип свойства.
    CALLBACK DataType (*propGetType)(qint32 prop);
    //ru Возвращает имя свойства.
    CALLBACK const char *(*propGetName)(qint32 prop);
    //ru Возвращает значение свойства в виде указателя на данные.
    CALLBACK qint32 (*propGetValue)(qint32 prop);
    //ru Возвращает значение свойства в формате uchar.
    CALLBACK uchar (*propToByte)(qint32 prop);
    //ru Возвращает значение свойства в формате qint32.
    CALLBACK qint32 (*propToInteger)(qint32 prop);
    //ru Возвращает значение свойства в формате float.
    CALLBACK qreal (*propToReal)(qint32 prop);
    //ru Возвращает значение свойства в виде C строки.
    CALLBACK const char *(*propToString)(qint32 prop);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ ресурсы ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Добавляет имя файла в общий список временных файлов
    //ru для последующего удаления файла.
    CALLBACK qint32 (*resAddFile)(const char *Name);
    //ru Добавляет иконку в ресурсы и в список временных файлов,
    //ru и возвращают имя временного файла.
    //TODO p - является свойством, которое содержит иконку?
    CALLBACK const char *(*resAddIcon)(qint32 p);
    //ru Добавляет строку в ресурсы и в список временных файлов.
    //TODO Что возвращает?
    CALLBACK const char *(*resAddStr)(const char *p);
    //ru Добавляет поток (данные) в ресурсы и в список временных файлов,
    //ru и возвращает имя временного файла.
    //ru Временный файл создаётся в папке %HiAsm%\compiler и существует до конца
    //ru работы с библиотекой.
    CALLBACK const char *(*resAddStream)(qint32 p);
    //ru Добавляет звук в ресурсы и в список временных файлов,
    //ru и возвращает имя временного файла.
    //ru Временный файл создаётся в папке %HiAsm%\compiler и существует до конца
    //ru работы с библиотекой.
    CALLBACK const char *(*resAddWave)(qint32 p);
    //ru Добавляет картинку в ресурсы и в список временных файлов,
    //ru и возвращает имя временного файла.
    //ru Временный файл создаётся в папке %HiAsm%\compiler и существует до конца
    //ru работы с библиотекой.
    CALLBACK const char *(*resAddBitmap)(qint32 p);
    //ru Добавляет меню в ресурсы и в список временных файлов.
    //[deprecated]
    CALLBACK const char *(*resAddMenu)(qint32 p);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ информационные сообщения ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Выводит строку Text в окно Отладка цветом Color
    //ru Всего возвращает 0.
    CALLBACK qint32 (*_Debug)(const char *Text, qint32 Color);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ среда ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает значение параметра среды по его индексу
    CALLBACK qint32 (*GetParam)(CgtParams index, void *value);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ массив ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает количество элементов в массиве.
    CALLBACK qint32 (*arrCount)(qint32 a);
    //ru Возвращает тип элементов в массиве.
    CALLBACK DataType (*arrType)(qint32 a);
    //ru Возвращает имя элемента с индексом Index.
    CALLBACK const char *(*arrItemName)(qint32 a, qint32 Index);
    //ru Возвращает значение элемента с индексом Index
    CALLBACK qint32 (*arrItemData)(qint32 a, qint32 Index);
    //ru Получаем элемент массива в виде свойства,
    //ru для дальнейшей работы с ним cgt::prop* функциями.
    CALLBACK qint32 (*arrGetItem)(qint32 a, qint32 Index);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ схема ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает >0, если запускаем cборку и запуск схемы в режиме отладки,
    //ru иначе 0.
    CALLBACK qint32 (*isDebug)(qint32 e);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ работа с данными ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает тип данных.
    CALLBACK DataType (*dtType)(qint32 d);
    //ru Возвращает данные в формате: строка в стиле C.
    CALLBACK const char *(*dtStr)(qint32 d);
    //ru Возвращает данные в формате: целое число.
    CALLBACK qint32 (*dtInt)(qint32 d);
    //ru Возвращает данные в формате: число с плавающей запятой.
    CALLBACK qreal (*dtReal)(qint32 d);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ шрифт ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает название шрифта.
    CALLBACK const char *(*fntName)(qint32 f);
    //ru Возвращает размер шрифта.
    CALLBACK qint32 (*fntSize)(qint32 f);
    //ru Возвращает стиль шрифта.
    CALLBACK uchar (*fntStyle)(qint32 f);
    //ru Возвращает цвет шрифта.
    CALLBACK qint32 (*fntColor)(qint32 f);
    //ru Возвращает кодировку шрифта.
    CALLBACK uchar (*fntCharSet)(qint32 f);
    //!~~~~~~~~~~~~~~~~элемент | пользовательские данные ~~~~~~~~~~~~~
    //!ru Судя по CodeGen.dpr, используется для хранения указателя (ID элемента) на самого себя.
    //ru Возвращает пользовательские данные элемента.
    //ru Коммент из hiasm5 - user data used in FTCG codegen.
    //ru Судя по всему, данные могут быть любого типа, ибо хранит указатель..
    CALLBACK qint32 (*elGetData)(qint32 e);
    //ru Устанавливает пользовательские данные элементу.
    //ru Коммент из hiasm5 - user data used in FTCG codegen.
    //ru Судя по всему, данные могут быть любого типа, ибо хранит указатель.
    CALLBACK void (*elSetData)(qint32 e, qint32 data);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ точки элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает тип данных точки.
    CALLBACK DataType (*ptGetDataType)(qint32 p);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ элемент ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает ID родительского контейнера элемента.
    CALLBACK qint32 (*elGetParent)(qint32 e);
    //ru Возвращает количество свойств в списке свойств(из панели свойств).
    //ru В RTCG используется аналогичная функция - elGetPropCount.
    //[deprecated]
    CALLBACK qint32 (*elGetPropertyListCount)(qint32 e);
    //ru Возвращает свойство из списка свойств (PropertyList).
    //[deprecated]
    CALLBACK qint32 (*elGetPropertyListItem)(qint32 e, qint32 i);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ список свойств элемента ~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает имя свойства.
    CALLBACK const char *(*plGetName)(qint32 p);
    //ru Возвращает описание свойства.
    CALLBACK const char *(*plGetInfo)(qint32 p);
    //ru Возвращает группу свойсва.
    CALLBACK const char *(*plGetGroup)(qint32 p);
    //ru Возвращает указатель на данные свойства.
    CALLBACK qint32 (*plGetProperty)(qint32 p);
    //ru Возвращает ID родительского элемента указанного свойства.
    CALLBACK qint32 (*plGetOwner)(qint32 p);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ точки элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает описание точки.
    CALLBACK const char *(*ptGetInfo)(qint32 p);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ свойства элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает ID элемента, прилинкованного к указанному свойству.
    CALLBACK qint32 (*propGetLinkedElement)(qint32 e, const char *propName);
    //ru Возвращает 1, если свойство помечено на перевод.
    CALLBACK qint32 (*propIsTranslate)(qint32 e, qint32 p);
    //ru Предназначение данной функции так и небыло найдено.
    //ru Всегда возвращает 0.
    //[deprecated]
    CALLBACK qint32 (*propGetLinkedElementInfo)(qint32 e, qint32 prop, char *_int);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ элемент - CI_PolyMulti ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает SDK контейнера по его индексу.
    CALLBACK qint32 (*elGetSDKByIndex)(qint32 e, qint32 index);
    //ru Возвращает количаство контейнеров полиморфного элемента(CI_PolyMulti).
    CALLBACK qint32 (*elGetSDKCount)(qint32 e);
    //ru Возвращает имя контейнера по индексу.
    CALLBACK const char *(*elGetSDKName)(qint32 e, qint32 index);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ схема ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает элемент родитель для данного SDK.
    //ru Возвращает 0, если контейнер не имеет родителя.
    CALLBACK qint32 (*sdkGetParent)(qint32 SDK);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ элемент ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает интерфейсы, предоставляемые элементом.
    //ru Содержимое поля Interfaces= из конфигурации элемента.
    CALLBACK const char *(*elGetInterface)(qint32 e);
    //ru Возвращает список классов, от которых наследуется элемент
    //ru Содержимое поля Inherit= из конфигурации элемента.
    CALLBACK const char *(*elGetInherit)(qint32 e);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ ресурсы ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает 1, если список ресурсов пуст, и 0 в противном случае.
    CALLBACK qint32 (*resEmpty)();
    //ru Устанавливает префикс для имен ресурсов.
    CALLBACK qint32 (*resSetPref)(const char *pref);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ информационные сообщения ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Добавляет информацию в информационную панель
    CALLBACK qint32 (*_Error)(qint32 line, qint32 e, const char *text);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ элемент ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Возвращает ID группы, к которой принадлежит элемент и 0, если группа отсутствует
    //[deprecated]
    CALLBACK qint32 (*elGetGroup)(qint32 e);
    //!~~~~~~~~~~~~~~~~~~~~~~~~ свойства элемента ~~~~~~~~~~~~~~~~~~~~~~~~~~
    //ru Сохраняет данные свойства в файл.
    //[deprecated]
    CALLBACK qint32 (*propSaveToFile)(qint32 p, const char *fileName);
};

Q_DECLARE_METATYPE(TCodeGenTools *)
