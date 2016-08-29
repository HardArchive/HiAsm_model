//Project
#include "value.h"
#include "cgt/CGTShare.h"

//STL

//Qt

Value::Value(DataType type, const QVariant &value, const QString &name, DataType subType)
    : m_type(type)
    , m_value(value)
    , m_name(name)
    , m_subType(subType)
{
}

QVariantMap Value::serialize() const
{
    QVariantMap data;
    data.insert("name", m_name);
    data.insert("type", m_type);
    data.insert("subType", m_subType);

    switch (m_type) {
    case data_int:
    case data_color:
    case data_flags: {
        data.insert("value", m_value.toInt());
        break;
    }
    case data_real: {
        data.insert("value", m_value.toReal());
        break;
    }
    case data_data: {
        data.insert("value", m_value);
        break;
    }
    case data_icon:
    case data_stream:
    case data_bitmap:
    case data_jpeg:
    case data_wave: {
        data.insert("value", m_value.toByteArray().toHex());
        break;
    }
    case data_array: {
        QVariantList array;
        for (const PValue v : m_value.value<Values>()) {
            array.append(v->serialize());
        }

        data.insert("ArrayValues", array);
        break;
    }
    case data_font: {
        const PValueFont font = m_value.value<PValueFont>();
        QVariantMap fontMap;
        fontMap.insert("name", font->name);
        fontMap.insert("size", font->size);
        fontMap.insert("style", font->style);
        fontMap.insert("color", font->color);
        fontMap.insert("charset", font->charset);

        data.insert("value", fontMap);
        break;
    }
    case data_element: {
        const PLinkedElementInfo info = m_value.value<PLinkedElementInfo>();
        QVariantMap infoMap;
        infoMap.insert("id", info->id);
        infoMap.insert("interface", info->interface);

        data.insert("value", infoMap);
        break;
    }
    default: {
        data.insert("value", m_value);
    }
    }

    return data;
}

void Value::setType(DataType type)
{
    m_type = type;
}

DataType Value::getType() const
{
    return m_type;
}

void Value::setName(const QString &name)
{
    m_name = name;
}

QString Value::getName() const
{
    return m_name;
}

void Value::setValue(const QVariant &value)
{
    m_value = value;
}

QVariant Value::getValue() const
{
    return m_value;
}

uchar Value::toByte() const
{
    if (!m_value.canConvert<uchar>())
        return uchar();

    return m_value.value<uchar>();
}

int Value::toInt() const
{
    if (!m_value.canConvert<int>())
        return int();

    return m_value.value<int>();
}

qreal Value::toReal() const
{
    if (!m_value.canConvert<qreal>())
        return qreal();

    return m_value.value<qreal>();
}

QString Value::toString() const
{
    if (!m_value.canConvert<QString>())
        return QString();

    return m_value.value<QString>();
}

DataType Value::getDataType() const
{
    return m_subType;
}

int Value::getArraySize() const
{
    if (!m_value.canConvert<Values>())
        return 0;

    return m_value.value<Values>().size();
}

void Value::setSubType(DataType type)
{
    m_subType = type;
}

DataType Value::getSubType() const
{
    return m_subType;
}

PValue Value::getArrayItemByIndex(uint index) const
{
    if (!m_value.canConvert<Values>())
        return nullptr;

    const Values arrayValues = m_value.value<Values>();
    if (index < uint(arrayValues.size()))
        return arrayValues[index];

    return nullptr;
}

QString Value::getArrayItemName(uint index) const
{
    const PValue arrValue = getArrayItemByIndex(index);
    if (!arrValue)
        return QString();

    return arrValue->getName();
}

PValueFont Value::toFont() const
{
    if (!m_value.canConvert<PValueFont>())
        return PValueFont();

    return m_value.value<PValueFont>();
}

PLinkedElementInfo Value::toLinkedElementInfo() const
{
    if (!m_value.canConvert<PLinkedElementInfo>())
        return PLinkedElementInfo();

    return m_value.value<PLinkedElementInfo>();
}
