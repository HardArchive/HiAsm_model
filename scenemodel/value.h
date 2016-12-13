#pragma once
//Project
#include "valuetypes.h"
#include "cgt/CGTShare.h"

//STL

//Qt
#include <QObject>
#include <QVariant>

class Value : public QVariant
{

private:
    //Self
    DataType m_type = data_null;

public:
    //Serialize
    QVariantMap serialize() const;

    //Self
    void setType(DataType type);
    DataType getType() const;

    //Byte
    uchar toByte() const;

    //Int
    int toInt() const;

    //Real
    qreal toReal() const;

    //String
    QString toString() const;

    //Array
    DataType getTypeArrayItem() const;
    int getArraySize() const;
    SharedArrayItem getArrayItemByIndex(int index) const;
    QString getArrayItemName(int index) const;

    //Font
    SharedValueFont toFont() const;

    //LinkedElementInfo
    SharedLinkedElementInfo toLinkedElementInfo() const;
};
