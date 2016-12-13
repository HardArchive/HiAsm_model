// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//Project
#include "point.h"
#include "container.h"
#include "element.h"
#include "scenemodel.h"
#include "cgt/cgt.h"
#include "cgt/globalcgt.h"

//STL

//Qt

Point::Point(qint32 id_point, QObject *parent)
    : QObject(parent)
    , m_model(parent->property("model").value<SceneModel *>())
{
    collectingData(id_point);
}

void Point::collectingData(qint32 id_point)
{
    PCodeGenTools cgt = GlobalCgt::getCgt();

    m_type = cgt->ptGetType(id_point);
    m_dataType = cgt->ptGetDataType(id_point);
    m_name = QString::fromLocal8Bit(cgt->ptGetName(id_point));
    m_dpeName = QString::fromLocal8Bit(cgt->pt_dpeGetName(id_point));
    m_info = QString::fromLocal8Bit(cgt->ptGetInfo(id_point));

    auto pId = cgt->ptGetRLinkPoint(id_point);
    if (pId) {
        m_connectPoint.element = cgt->ptGetParent(pId);
        m_connectPoint.point = QString::fromLocal8Bit(cgt->ptGetName(pId));
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

SceneModel *Point::getModel()
{
    return m_model;
}
