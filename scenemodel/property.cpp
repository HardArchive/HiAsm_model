// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//Project
#include "property.h"
#include "element.h"
#include "valuetypes.h"
#include "scenemodel.h"
#include "cgt/cgt.h"
#include "cgt/globalcgt.h"

//STL
#include <limits>

//Qt
#include <QTemporaryFile>
#include <QDebug>
#include <QUuid>

Property::Property(qint32 id, QObject *parent)
    : QObject(parent)
    , m_model(parent->property("model").value<SceneModel *>())
{
    collectingData(id);
}

Property::Property(DataType type, const QVariant &data, const QString &name)
{
    m_name = name;
    m_type = type;
    m_value.setType(type);
    m_value.setValue(data);
    m_value.setName(name);
}

void Property::collectingData(qint32 idProp)
{
    PCodeGenTools cgt = GlobalCgt::getCgt();

    m_name = QString::fromLocal8Bit(cgt->propGetName(idProp));
    m_type = cgt->propGetType(idProp);
    qint32 id_value = cgt->propGetValue(idProp);

    switch (m_type) {
    case data_int:
    case data_color:
    case data_flags: {
        setValue(m_type, cgt->propToInteger(idProp));
        break;
    }
    case data_real: {
        setValue(m_type, cgt->propToReal(idProp));
        break;
    }
    case data_str:
    case data_comboEx:
    case data_list:
    case data_script:
    case data_code: {
        setValue(m_type, QString::fromLocal8Bit(cgt->propToString(idProp)));
        break;
    }
    case data_data: {
        const DataType dataType = cgt->dtType(id_value);
        switch (dataType) {
        case data_int:
            setValue(m_type, cgt->dtInt(id_value), QString(), dataType);
            break;
        case data_str:
            setValue(m_type, cgt->dtStr(id_value), QString(), dataType);
            break;
        case data_real:
            setValue(m_type, cgt->dtReal(id_value), QString(), dataType);
            break;
        default:
            setValue(m_type);
            break;
        }
        break;
    }
    case data_combo: {
        setValue(m_type, cgt->propToByte(idProp));
        break;
    }
    case data_icon: {
        if (!strcmp(cgt->resAddIcon(idProp), "ASMA")) {
            break;
        }
    }
    case data_stream:
    case data_bitmap:
    case data_jpeg:
    case data_wave: {
        static QString nameRandom = QUuid::createUuid().toString() + ".wtf";
        static QString filePath = QDir::toNativeSeparators(QDir::tempPath() + QDir::separator() + nameRandom);

        cgt->propSaveToFile(idProp, filePath.toStdString().data());
        QFile file(filePath);
        if (file.size()) {
            file.open(QIODevice::ReadOnly);
            setValue(m_type, file.readAll());
            file.close();
        }
        file.remove();

        break;
    }
    case data_array: {
        qint32 arrCount = cgt->arrCount(id_value);
        DataType arrItemType = cgt->arrType(id_value);
        Values arrayItems;

        for (qint32 i = 0; i < arrCount; ++i) {
            const qint32 id_prop = cgt->arrGetItem(id_value, i);

            QString name = QString::fromLocal8Bit(cgt->arrItemName(id_value, i));
            QVariant data;
            switch (arrItemType) {
            case data_int:
                data = cgt->propToInteger(id_prop);
                break;
            case data_str:
                data = QString::fromLocal8Bit(cgt->propToString(id_prop));
                break;
            case data_real:
                data = cgt->propToReal(id_prop);
                break;
            default:
                break;
            }

            arrayItems.append(SharedValue::create(arrItemType, data, name));
        }

        setValue(m_type, QVariant::fromValue(arrayItems), QString(), arrItemType);
        break;
    }
    case data_font: {
        const SharedValueFont font = SharedValueFont::create();
        font->name = QString::fromLocal8Bit(cgt->fntName(id_value));
        font->size = cgt->fntSize(id_value);
        font->style = cgt->fntStyle(id_value);
        font->color = cgt->fntColor(id_value);
        font->charset = cgt->fntCharSet(id_value);

        setValue(m_type, QVariant::fromValue(font));
        break;
    }
    case data_element: {
        const Element *e = getParent();
        if (!e)
            return;

        char buf[PATH_MAX];
        qint32 linkedElement = cgt->propGetLinkedElementInfo(e->getId(), idProp, buf);
        if (linkedElement) {
            SharedLinkedElementInfo elementInfo = SharedLinkedElementInfo::create();
            elementInfo->id = linkedElement;
            elementInfo->interface = QString::fromLocal8Bit(buf);

            setValue(m_type, QVariant::fromValue(elementInfo));
        }
        break;
    }
    default:
        break;
    }
}

QVariantMap Property::serialize() const
{
    QVariantMap data;
    data.insert("name", m_name);
    data.insert("type", m_type);
    data.insert("value", m_value.serialize());

    return data;
}

void Property::setName(const QString &name)
{
    m_name = name;
}

QString Property::getName() const
{
    return m_name;
}

Element *Property::getParent() const
{
    return qobject_cast<Element *>(parent());
}

void Property::setType(DataType type)
{
    m_type = type;
}

DataType Property::getType() const
{
    return m_type;
}

void Property::setIsDefProp(bool value)
{
    m_isDefProp = value;
}

bool Property::getIsDefProp() const
{
    return m_isDefProp;
}

void Property::setValue(DataType type, const QVariant &data, const QString &name, DataType arrayType)
{
    m_value.setType(type);
    m_value.setValue(data);
    m_value.setName(name);
    m_value.setSubType(arrayType);
}

Value *Property::getValue()
{
    return &m_value;
}

uchar Property::toByte() const
{
    return m_value.toByte();
}

qint32 Property::toInt() const
{
    return m_value.toInt();
}

qreal Property::toReal() const
{
    return m_value.toReal();
}

QString Property::toString() const
{
    return m_value.toString();
}

SharedLinkedElementInfo Property::toLinkedElementInfo() const
{
    return m_value.toLinkedElementInfo();
}

SceneModel *Property::getModel()
{
    return m_model;
}
