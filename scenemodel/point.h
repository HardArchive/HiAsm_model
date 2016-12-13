#pragma once

//Project
#include "cgt/CGTShare.h"

//STL

//Qt
#include <QObject>
#include <QDebug>

class SceneModel;
class Element;

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
        qint32 element{};
        QString point;
    } m_connectPoint;

    //CGT
    TCodeGenTools *m_cgt{};

    //Model
    SceneModel *m_model{};

private:
    Q_PROPERTY(SceneModel *model READ getModel)
    Q_PROPERTY(TCodeGenTools *cgt READ getCgt)

public:
    explicit Point(qint32 id_point, QObject *parent);

private:
    void collectingData(qint32 id_point);

public:
    //Serialize
    QVariantMap serialize() const;

    //Self
    Element *getParent() const;

    void setType(PointType type);
    PointType getType() const;

    void setDataType(DataType dataType);
    DataType getDataType() const;

    qint32 getIndex() const;

    void setName(const QString &name);
    QString getName() const;

    void setDpeName(const QString &dpeName);
    QString getDpeName() const;

    void setInfo(const QString &info);
    QString getInfo() const;

    Point *getLinkPoint() const;
    Point *getRLinkPoint() const;

    //CGT
    TCodeGenTools *getCgt();

    //Model
    SceneModel *getModel();
};
