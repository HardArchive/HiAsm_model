#pragma once

//Project
#include "types.h"
#include "cgt/CGTShare.h"

//STL

//Qt
#include <QObject>
#include <QDebug>

class Point : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY(Point)

private:
    //Self
    PointType m_type{};
    DataType m_dataType{};
    QString m_name;
    QString m_dpeName;
    QString m_info;
    struct {
        int element{};
        QString point;
    } m_connectPoint;

    //CGT
    PCodeGenTools m_cgt{};

    //Model
    PSceneModel m_model{};

private:
    Q_PROPERTY(PSceneModel model READ getModel)
    Q_PROPERTY(PCodeGenTools cgt READ getCgt)

public:
    explicit Point(int id_point, QObject *parent);

private:
    void collectingData(int id_point);

public:
    //Serialize
    QVariantMap serialize() const;

    //Self
    Element * getParent() const;

    void setType(PointType type);
    PointType getType() const;

    void setDataType(DataType dataType);
    DataType getDataType() const;

    int getIndex() const;

    void setName(const QString &name);
    QString getName() const;

    void setDpeName(const QString &dpeName);
    QString getDpeName() const;

    void setInfo(const QString &info);
    QString getInfo() const;

    Point * getLinkPoint() const;
    Point * getRLinkPoint() const;

    //CGT
    PCodeGenTools getCgt();

    //Model
    PSceneModel getModel();
};
