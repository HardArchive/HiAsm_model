//Project
#include "container.h"
#include "element.h"
#include "scenemodel.h"
#include "cgt/cgt.h"

//STL

//Qt

Container::Container(qintptr id_sdk, QObject *parent)
    : QObject(parent)
    , m_id(id_sdk)
    , m_cgt(parent->property("cgt").value<TCodeGenTools *>())
    , m_model(parent->property("model").value<SceneModel *>())
{
    m_model->addContainerToMap(this);
    collectingData();
}

void Container::collectingData()
{
    qint32 countElements = m_cgt->sdkGetCount(m_id);
    for (qint32 i = 0; i < countElements; ++i) {
        qintptr id_element = m_cgt->sdkGetElement(m_id, i);

        //ru Добавляем элемент в контейнер
        addElement(new Element(id_element, this));
    }
}

QVariantMap Container::serialize() const
{
    QVariantMap data;
    data.insert("id", m_id);
    data.insert("name", m_name);

    QVariantList elements;
    for (const Element *e : m_elements) {
        elements.append(e->serialize());
    }

    QVariantMap container;
    if (!data.isEmpty())
        container.insert("Data", data);
    if (!elements.isEmpty())
        container.insert("Elements", elements);

    return container;
}

qint32 Container::getId() const
{
    return m_id;
}

Element *Container::getParent() const
{
    return qobject_cast<Element *>(parent());
}

QString Container::getName() const
{
    return m_name;
}

TCodeGenTools *Container::getCgt()
{
    return m_cgt;
}

SceneModel *Container::getModel() const
{
    return m_model;
}

void Container::setName(const QString &name)
{
    m_name = name;
}

qint32 Container::getCountElements() const
{
    return m_elements.size();
}

Element *Container::getElementByIndex(qint32 index) const
{
    if (index < m_elements.size())
        return m_elements[index];

    return nullptr;
}

qint32 Container::getIdElementByIndex(qint32 index) const
{
    const Element *e = getElementByIndex(index);
    if (!e)
        return -1;

    return e->getId();
}

Element *Container::getElementByName(const QString &name) const
{
    for (Element *e : m_elements) {
        if (QString::compare(e->getClassName(), name, Qt::CaseInsensitive) == 0) {
            return e;
        }
    }

    return 0;
}

qint32 Container::getIdElementByName(const QString &name) const
{
    Element *e = getElementByName(name);
    if (e)
        return e->getId();

    return -1;
}

Element *Container::addElement(Element *element)
{
    m_elements.append(element);
    return element;
}

void Container::removeElement(qint32 index)
{
    m_elements.remove(index);
}
