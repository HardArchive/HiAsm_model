//Project
#include "element.h"
#include "container.h"
#include "point.h"
#include "property.h"
#include "scenemodel.h"
#include "cgt/cgt.h"

//STL

//Qt

Element::Element(const QString &name, qint32 id_element, qint32 X, qint32 Y, QObject *parent)
    : QObject(parent)
    , m_id(id_element)
    , m_posX(X)
    , m_posY(Y)
    , m_model(parent->property("model").value<SceneModel *>())
{
    m_model->addElementToMap(this);

    Package *package = m_model->getPackage();
    const SharedConfElement conf = package->getElementByName(name);
}

Element::Element(qintptr id_element, QObject *parent)
    : QObject(parent)
    , m_id(id_element)
    , m_cgt(parent->property("cgt").value<TCodeGenTools *>())
    , m_model(parent->property("model").value<SceneModel *>())
{
    m_model->addElementToMap(this);
    collectingData();
}

void Element::collectingData()
{
    m_classIndex = m_cgt->elGetClassIndex(m_id);
    m_flags = m_cgt->elGetFlag(m_id);
    m_group = m_cgt->elGetGroup(m_id);
    m_linkIs = m_cgt->elLinkIs(m_id);
    m_linkMain = m_cgt->elLinkMain(m_id);
    m_cgt->elGetPos(m_id, m_posX, m_posY);
    m_cgt->elGetSize(m_id, m_sizeW, m_sizeH);
    m_className = QString::fromLocal8Bit(m_cgt->elGetClassName(m_id));
    m_codeName = QString::fromLocal8Bit(m_cgt->elGetCodeName(m_id));
    m_inherit = QString::fromLocal8Bit(m_cgt->elGetInherit(m_id));
    m_interface = QString::fromLocal8Bit(m_cgt->elGetInterface(m_id));
    m_infSub = QString::fromLocal8Bit(m_cgt->elGetInfSub(m_id));
    qint32 ptCount = m_cgt->elGetPtCount(m_id);
    qint32 propCount = m_cgt->elGetPropCount(m_id);

    //ru Получаем информацию о точках
    for (qint32 i = 0; i < ptCount; ++i) {
        qintptr pointId = m_cgt->elGetPt(m_id, i);
        addPoint(new Point(pointId, this));
    }

    //ru Получаем информацию о свойствах
    for (qint32 i = 0; i < propCount; ++i) {
        qintptr propId = m_cgt->elGetProperty(m_id, i);
        addProperty(new Property(propId, this));
    }

    if (fcgt::isLink(m_flags))
        return;

    //ru Элемент содержит контейнер(ы)
    if (fcgt::isMulti(m_flags)) {
        //ru Элемен содержит полиморфный контейнер
        if (fcgt::isPolyMulti(m_classIndex)) {
            //ru Получаем к-во контейнеров, которое содержит текущий элемент
            qint32 countContainers = m_cgt->elGetSDKCount(m_id);

            for (qint32 i = 0; i < countContainers; ++i) {
                //ru Получаем ID контейнера
                qintptr id_sdk = m_cgt->elGetSDKByIndex(m_id, i);
                QString name = QString::fromLocal8Bit(m_cgt->elGetSDKName(id_sdk, i));

                //ru Добавляем контейнер в элемент
                addContainer(new Container(id_sdk, this))->setName(name);
            }
        } else { //ru Элемент содержит обычный контейнер

            //ru Получаем ID контейнера элемента
            qintptr id_sdk = m_cgt->elGetSDK(m_id);

            //ru Добавляем контейнер в элемент
            addContainer(new Container(id_sdk, this));
        }
    }
}

QVariantMap Element::serialize() const
{
    QVariantMap data;
    data.insert("id", m_id);
    //data.insert("userData", m_userData);
    data.insert("classIndex", m_classIndex);
    data.insert("flags", qint32(m_flags));
    data.insert("group", m_group);
    data.insert("linkIs", m_linkIs);
    data.insert("linkMain", m_linkMain);
    data.insert("posX", m_posX);
    data.insert("posY", m_posY);
    data.insert("sizeW", m_sizeW);
    data.insert("sizeH", m_sizeH);
    data.insert("className", m_className);
    data.insert("codeName", m_codeName);
    data.insert("interface", m_interface);
    data.insert("inherit", m_inherit);
    data.insert("infSub", m_infSub);

    QVariantList containers;
    for (const Container *c : m_containers) {
        containers.append(c->serialize());
    }

    QVariantList points;
    for (const Point *p : m_points) {
        points.append(p->serialize());
    }

    QVariantList properties;
    for (const Property *p : m_properties) {
        properties.append(p->serialize());
    }

    QVariantMap element;
    if (!data.isEmpty())
        element.insert("Data", data);
    if (!containers.isEmpty())
        element.insert("Containers", containers);
    if (!points.isEmpty())
        element.insert("Points", points);
    if (!properties.isEmpty())
        element.insert("Properties", properties);

    return element;
}

qint32 Element::getId() const
{
    return m_id;
}

Container *Element::getParent() const
{
    return qobject_cast<Container *>(parent());
}

void Element::setUserData(qint32 userData)
{
    m_userData = userData;
}

qintptr Element::getUserData() const
{
    return m_userData;
}

void Element::setClassIndex(ElementClass classIndex)
{
    m_classIndex = classIndex;
}

ElementClass Element::getClassIndex()
{
    return m_classIndex;
}

void Element::setFlags(const ElementFlgs &flags)
{
    m_flags = flags;
}

ElementFlags Element::getFlags() const
{
    return ElementFlags(qint32(m_flags));
}

void Element::setGroup(qint32 group)
{
    m_group = group;
}

qint32 Element::getGroup() const
{
    return m_group;
}

void Element::setLinkIs(bool linkIs)
{
    m_linkIs = linkIs;
}

bool Element::getLinkIs() const
{
    return m_linkIs;
}

void Element::setLinkMain(qintptr linkMain)
{
    m_linkMain = linkMain;
}

qintptr Element::getLinkMain() const
{
    return m_linkMain;
}

void Element::setPosX(qint32 posX)
{
    m_posX = posX;
}

qint32 Element::getPosX() const
{
    return m_posX;
}

void Element::setPosY(qint32 posY)
{
    m_posY = posY;
}

qint32 Element::getPosY() const
{
    return m_posY;
}

void Element::setSizeW(qint32 sizeW)
{
    m_sizeW = sizeW;
}

qint32 Element::getSizeW() const
{
    return m_sizeW;
}

void Element::setSizeH(qint32 sizeH)
{
    m_sizeH = sizeH;
}

qint32 Element::getSizeH() const
{
    return m_sizeH;
}

void Element::setClassName(const QString &className)
{
    m_className = className;
}

QString Element::getClassName() const
{
    return m_className;
}

void Element::setCodeName(const QString &name)
{
    m_codeName = name;
}

QString Element::getCodeName() const
{
    return m_codeName;
}

void Element::setInterface(const QString &interface)
{
    m_interface = interface;
}

QString Element::getInterface() const
{
    return m_interface;
}

void Element::setInherit(const QString &inherit)
{
    m_inherit = inherit;
}

QString Element::getInherit() const
{
    return m_inherit;
}

void Element::setInfSub(const QString &infSub)
{
    m_infSub = infSub;
}

QString Element::getInfSub() const
{
    return m_infSub;
}

TCodeGenTools *Element::getCgt()
{
    return m_cgt;
}

SceneModel *Element::getModel()
{
    return m_model;
}

qint32 Element::getCountContainers() const
{
    return m_containers.size();
}

Container *Element::getContainer() const
{
    if (m_containers.isEmpty())
        return nullptr;

    return m_containers[0];
}

qint32 Element::getIdContainer() const
{
    const Container *c = getContainer();
    if (!c)
        return 0;

    return c->getId();
}

Container *Element::getContainerByIndex(qint32 index) const
{
    if (index < m_containers.size())
        return m_containers[index];
    else
        return nullptr;
}

qint32 Element::getIdContainerByIndex(qint32 index) const
{
    const Container *c = getContainerByIndex(index);
    if (!c)
        return 0;

    return c->getId();
}

Container *Element::addContainer(Container *container)
{
    m_containers.append(container);
    return container;
}

void Element::removeContainer(qint32 index)
{
    m_containers.remove(index);
}

qint32 Element::getCountPoints() const
{
    return m_points.size();
}

qint32 Element::getPointIndexOfType(const Point *id_point) const
{
    if (!id_point)
        return -1;

    uint idx = 0;
    for (const Point *p : m_points) {
        if (p == id_point) {
            return idx;
        } else if (id_point->getType() == p->getType()) {
            ++idx;
        }
    }

    return -1;
}

Point *Element::getPointByIndex(qint32 index) const
{
    if (index < m_points.size())
        return m_points[index];
    else
        return nullptr;
}

Point *Element::getIdPointByIndex(qint32 index) const
{
    return getPointByIndex(index);
}

Point *Element::getPointByName(const QString &name) const
{
    for (Point *p : m_points) {
        if (QString::compare(p->getName(), name, Qt::CaseInsensitive) == 0) {
            return p;
        }
    }

    return nullptr;
}

Point *Element::getIdPointByName(const QString &name) const
{
    return getPointByName(name);
}

Point *Element::addPoint(Point *point)
{
    m_points.append(point);
    return point;
}

void Element::removePoint(qint32 index)
{
    m_points.remove(index);
}

qint32 Element::getCountProps() const
{
    return m_properties.size();
}

Property *Element::getPropertyByIndex(qint32 index) const
{
    if (index < m_properties.size())
        return m_properties[index];

    return nullptr;
}

Property *Element::getIdPropertyByIndex(qint32 index) const
{
    return getPropertyByIndex(index);
}

Property *Element::getPropertyById(Property *id_prop) const
{
    if (!id_prop)
        return nullptr;

    for (Property *p : m_properties) {
        if (p == id_prop) {
            return p;
        }
    }

    return nullptr;
}

Property *Element::getPropertyByName(const QString &name) const
{
    for (Property *p : m_properties) {
        if (QString::compare(p->getName(), name, Qt::CaseInsensitive) == 0) {
            return p;
        }
    }

    return nullptr;
}

Property *Element::getIdPropertyByName(const QString &name) const
{
    Property *p = getPropertyByName(name);
    if (!p)
        return nullptr;

    return p;
}

Property *Element::addProperty(Property *property)
{
    m_properties.append(property);
    return property;
}

void Element::removeProperty(qint32 index)
{
    m_points.remove(index);
}
