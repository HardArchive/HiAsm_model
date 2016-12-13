//Project
#include "value.h"
#include "cgt/CGTShare.h"

//STL

//Qt

QVariantMap Value::serialize() const
{
    /*
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
        for (const SharedValue &v : m_value.value<Values>()) {
            array.append(v->serialize());
        }

        data.insert("ArrayValues", array);
        break;
    }
    case data_font: {
        const SharedValueFont font = m_value.value<SharedValueFont>();
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
        const SharedLinkedElementInfo info = value<SharedLinkedElementInfo>();
        QVariantMap infoMap;
        infoMap.insert("id", info->id);
        infoMap.insert("interface", info->interface);

        data.insert("value", infoMap);
        break;
    }
    default: {
        //data.insert("value", value);
    }
    }

    return data;
    */

    return QVariantMap();
}


void Value::setType(DataType type)
{
    m_type = type;
}

DataType Value::getType() const
{
    return m_type;
}

uchar Value::toByte() const
{
    if (!canConvert<uchar>())
        return uchar();

    return value<uchar>();
}

int Value::toInt() const
{
    if (!canConvert<int>())
        return int();

    return value<int>();
}

qreal Value::toReal() const
{
    if (!canConvert<qreal>())
        return qreal();

    return value<qreal>();
}

QString Value::toString() const
{
    if (!canConvert<QString>())
        return QString();

    return value<QString>();
}

DataType Value::getTypeArrayItem() const
{
    if (!canConvert<SharedArrayValue>())
        return data_null;

    return value<SharedArrayValue>()->getType();
}

int Value::getArraySize() const
{
    if (!canConvert<SharedArrayValue>())
        return -1;

    return value<SharedArrayValue>()->size();
}

SharedArrayItem Value::getArrayItemByIndex(int index) const
{
    if (!canConvert<SharedArrayValue>())
        return SharedArrayItem();

    const SharedArrayValue &arrayValues = value<SharedArrayValue>();
    if (index < arrayValues->size())
        return arrayValues->at(index);

    return SharedArrayItem();
}

QString Value::getArrayItemName(int index) const
{
    const SharedArrayItem arrItem = getArrayItemByIndex(index);
    if (!arrItem)
        return QString();

    return arrItem->name;
}

SharedValueFont Value::toFont() const
{
    if (!canConvert<SharedValueFont>())
        return SharedValueFont();

    return value<SharedValueFont>();
}

SharedLinkedElementInfo Value::toLinkedElementInfo() const
{
    if (!canConvert<SharedLinkedElementInfo>())
        return SharedLinkedElementInfo();

    return value<SharedLinkedElementInfo>();
}
