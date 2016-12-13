#pragma once

//Project
#include "value.h"
#include "valuetypes.h"
#include "cgt/CGTShare.h"

//STL

//Qt
#include <QObject>

class SceneModel;
class Element;

class Property : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Property)

private:
    //Self
    QString m_name;
    DataType m_type;
    bool m_isDefProp{};

    //Value
    Value m_value;

public:
    explicit Property(qint32 id, QObject *parent);
    Property();

private:
    void collectingData(qint32 idProp);

public:
    //Serialize
    QVariantMap serialize() const;

    //Self
    void setName(const QString &name);
    QString getName() const;
    Element *getParent() const;
    bool getIsDefProp() const;

    void setType(DataType type);
    DataType getType() const;

    //Value
    void setValue(const QVariant &data);
    void setValue(const QVariant &data, DataType type);
    Value *value();
};
