#pragma once

//Project
#include "cgt/CGTShare.h"

//STL

//Qt
#include <QObject>
#include <QString>

class SceneModel;
class Container;
class Point;
class Property;

class Element : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY(Element)

private:
    //Self
    qint32 m_id{};
    qint32 m_userData{};
    ElementClass m_classIndex{};
    ElementFlgs m_flags{};
    qint32 m_group{};
    bool m_linkIs{};
    qint32 m_linkMain{};
    qint32 m_posX{};
    qint32 m_posY{};
    qint32 m_sizeW{};
    qint32 m_sizeH{};
    QString m_className;
    QString m_codeName;
    QString m_interface;
    QString m_inherit;
    QString m_infSub;

    //CGT
    TCodeGenTools *m_cgt{};

    //Model
    SceneModel *m_model{};

    //Container
    QVector<Container *> m_containers;

    //Point
    QVector<Point *> m_points;

    //Property
    QVector<Property *> m_properties;

private:
    Q_PROPERTY(SceneModel *model READ getModel)
    Q_PROPERTY(TCodeGenTools *cgt READ getCgt)

public:
    explicit Element(const QString &name, qint32 id_element, qint32 X, qint32 Y, QObject *parent);
    explicit Element(qint32 id_element, QObject *parent);

private:
    void collectingData();

public:
    //Serialize
    QVariantMap serialize() const;

    //Self
    qint32 getId() const;
    Container *getParent() const;

    void setUserData(qint32 userData);
    qint32 getUserData() const;

    void setClassIndex(ElementClass classIndex);
    ElementClass getClassIndex();

    void setFlags(const ElementFlgs &flags);
    ElementFlags getFlags() const;

    void setGroup(qint32 group);
    qint32 getGroup() const;

    void setLinkIs(bool linkIs);
    bool getLinkIs() const;

    void setLinkMain(qint32 linkMain);
    qint32 getLinkMain() const;

    void setPosX(qint32 posX);
    qint32 getPosX() const;

    void setPosY(qint32 posY);
    qint32 getPosY() const;

    void setSizeW(qint32 sizeW);
    qint32 getSizeW() const;

    void setSizeH(qint32 sizeH);
    qint32 getSizeH() const;

    void setClassName(const QString &className);
    QString getClassName() const;

    void setCodeName(const QString &name);
    QString getCodeName() const;

    void setInterface(const QString &interface);
    QString getInterface() const;

    void setInherit(const QString &inherit);
    QString getInherit() const;

    void setInfSub(const QString &infSub);
    QString getInfSub() const;

    //CGT
    TCodeGenTools *getCgt();

    //Model
    SceneModel *getModel();

    //Container
    qint32 getCountContainers() const;
    Container *getContainer() const;
    qint32 getIdContainer() const;
    Container *getContainerByIndex(qint32 index) const;
    qint32 getIdContainerByIndex(qint32 index) const;
    Container *addContainer(Container *container);
    void removeContainer(qint32 index);

    //Point
    qint32 getCountPoints() const;
    qint32 getPointIndexOfType(const Point *id_point) const;
    Point *getPointByIndex(qint32 index) const;
    Point *getIdPointByIndex(qint32 index) const;
    Point *getPointByName(const QString &name) const;
    Point *getIdPointByName(const QString &name) const;
    Point *addPoint(Point *point);
    void removePoint(qint32 index);

    //Property
    qint32 getCountProps() const;
    Property *getPropertyByIndex(qint32 index) const;
    Property *getIdPropertyByIndex(qint32 index) const;
    Property *getPropertyById(Property *id_prop) const;
    Property *getPropertyByName(const QString &name) const;
    Property *getIdPropertyByName(const QString &name) const;
    Property *addProperty(Property *property);
    void removeProperty(qint32 index);
};
