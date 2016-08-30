//Project
#include "point.h"
#include "container.h"
#include "element.h"
#include "scenemodel.h"
#include "cgt/cgt.h"

//STL

//Qt

Point::Point(qint32 id_point, QObject *parent)
    : QObject(parent)
    , m_cgt(parent->property("cgt").value<TCodeGenTools *>())
    , m_model(parent->property("model").value<SceneModel *>())
{
    collectingData(id_point);
}

void Point::collectingData(qint32 id_point)
{
    m_type = m_cgt->ptGetType(id_point);
    m_dataType = m_cgt->ptGetDataType(id_point);
    m_name = QString::fromLocal8Bit(m_cgt->ptGetName(id_point));
    m_dpeName = QString::fromLocal8Bit(m_cgt->pt_dpeGetName(id_point));
    m_info = QString::fromLocal8Bit(m_cgt->ptGetInfo(id_point));

    auto pId = m_cgt->ptGetRLinkPoint(id_point);
    if (pId) {
        m_connectPoint.element = m_cgt->ptGetParent(pId);
        m_connectPoint.point = QString::fromLocal8Bit(m_cgt->ptGetName(pId));
    }
}

QVariantMap Point::serialize() const
{
    QVariantMap data;
    data.insert("type", m_type);
    data.insert("dataType", m_dataType);
    data.insert("name", m_name);
    data.insert("dpeName", m_dpeName);
    data.insert("info", m_info);

    return data;
}

Element *Point::getParent() const
{
    return qobject_cast<Element *>(parent());
}

void Point::setType(PointType type)
{
    m_type = type;
}

PointType Point::getType() const
{
    return m_type;
}

void Point::setDataType(DataType dataType)
{
    m_dataType = dataType;
}

DataType Point::getDataType() const
{
    return m_dataType;
}

qint32 Point::getIndex() const
{
    return getParent()->getPointIndexOfType(this);
}

void Point::setName(const QString &name)
{
    m_name = name;
}

QString Point::getName() const
{
    return m_name;
}

void Point::setDpeName(const QString &dpeName)
{
    m_dpeName = dpeName;
}

QString Point::getDpeName() const
{
    return m_dpeName;
}

void Point::setInfo(const QString &info)
{
    m_info = info;
}

QString Point::getInfo() const
{
    return m_info;
}

Point *Point::getLinkPoint() const
{
    return nullptr; //TODO доработать
}

Point *Point::getRLinkPoint() const
{
    if (m_connectPoint.element) {
        auto e = m_model->getElementById(m_connectPoint.element);
        return e->getPointByName(m_connectPoint.point);
    }

    return nullptr;
}

TCodeGenTools * Point::getCgt()
{
    return m_cgt;
}

SceneModel *Point::getModel()
{
    return m_model;
}
