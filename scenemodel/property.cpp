//Project
#include "property.h"
#include "element.h"
#include "valuetypes.h"
#include "scenemodel.h"
#include "cgt/emulatecgt.h"

//STL
#include <limits>

//Qt
#include <QTemporaryFile>
#include <QDebug>
#include <QUuid>

Property::Property(qint32 id, QObject *parent)
    : QObject(parent)
{
    collectingData(id);
}

Property::Property()
{
}

void Property::collectingData(qint32 idProp)
{
    TCodeGenTools *cgt = EmulateCgt::getCgt();

    m_name = QString::fromLocal8Bit(cgt->propGetName(idProp));
    m_type = cgt->propGetType(idProp);
    qint32 id_value = cgt->propGetValue(idProp);

    switch (m_type) {
    case data_int:
    case data_color:
    case data_flags: {
        setValue(cgt->propToInteger(idProp), m_type);
        break;
    }
    case data_real: {
        setValue(cgt->propToReal(idProp), m_type);
        break;
    }
    case data_str:
    case data_comboEx:
    case data_list:
    case data_script:
    case data_code: {
        setValue(QString::fromLocal8Bit(cgt->propToString(idProp)), m_type);
        break;
    }
    case data_data: {
        const DataType dataType = cgt->dtType(id_value);
        switch (dataType) {
        case data_int:
            setValue(cgt->dtInt(id_value), dataType);
            break;
        case data_str:
            setValue(cgt->dtStr(id_value), dataType);
            break;
        case data_real:
            setValue(cgt->dtReal(id_value), dataType);
            break;
        default:
            setValue(m_type, dataType);
            break;
        }
        break;
    }
    case data_combo: {
        setValue(cgt->propToByte(idProp), m_type);
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
            setValue(file.readAll(), m_type);
            file.close();
        }
        file.remove();

        break;
    }
    case data_array: {
        qint32 arrCount = cgt->arrCount(id_value);
        DataType arrItemType = cgt->arrType(id_value);
        SharedArrayValue arrayItems = SharedArrayValue::create(arrItemType);

        for (qint32 i = 0; i < arrCount; ++i) {
            const qint32 id_prop = cgt->arrGetItem(id_value, i);
            SharedArrayItem item = SharedArrayItem::create();

            item->name = QString::fromLocal8Bit(cgt->arrItemName(id_value, i));
            switch (arrItemType) {
            case data_int:
                item->data = cgt->propToInteger(id_prop);
                break;
            case data_str:
                item->data = QString::fromLocal8Bit(cgt->propToString(id_prop));
                break;
            case data_real:
                item->data = cgt->propToReal(id_prop);
                break;
            default:
                break;
            }

            arrayItems->append(item);
        }

        setValue(QVariant::fromValue(arrayItems), m_type);
        break;
    }
    case data_font: {
        const SharedValueFont font = SharedValueFont::create();
        font->name = QString::fromLocal8Bit(cgt->fntName(id_value));
        font->size = cgt->fntSize(id_value);
        font->style = cgt->fntStyle(id_value);
        font->color = cgt->fntColor(id_value);
        font->charset = cgt->fntCharSet(id_value);

        setValue(QVariant::fromValue(font), m_type);
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
    data.insert("type", m_value.getType());
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
    m_value.setType(type);
}

DataType Property::getType() const
{
    return m_value.getType();
}

bool Property::getIsDefProp() const
{
    return m_isDefProp;
}

void Property::setValue(const QVariant &data)
{
    m_value.setValue(data);
}

void Property::setValue(const QVariant &data, DataType type)
{
    m_value.setValue(data);
    m_value.setType(type);
}

Value *Property::value()
{
    return &m_value;
}
