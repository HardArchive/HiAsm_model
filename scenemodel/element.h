#pragma once

//Project
#include "types.h"
#include "cgt/CGTShare.h"

//STL

//Qt
#include <QObject>
#include <QString>

class SceneModel;

class Element : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY(Element)

private:
    //Self
    qintptr m_id{};
    qintptr m_userData{};
    ElementClass m_classIndex{};
    ElementFlgs m_flags{};
    int m_group{};
    bool m_linkIs{};
    qintptr m_linkMain{};
    int m_posX{};
    int m_posY{};
    int m_sizeW{};
    int m_sizeH{};
    QString m_className;
    QString m_codeName;
    QString m_interface;
    QString m_inherit;
    QString m_infSub;

    //CGT
    PCodeGenTools m_cgt{};

    //Model
    SceneModel * m_model{};

    //Container
    Containers m_containers;

    //Point
    Points m_points;

    //Property
    Properties m_properties;

private:
    Q_PROPERTY(SceneModel * model READ getModel)
    Q_PROPERTY(PCodeGenTools cgt READ getCgt)

public:
    explicit Element(const QString &name, qintptr id_element, int X, int Y, QObject *parent);
    explicit Element(qintptr id_element, QObject *parent);

private:
    void collectingData();

public:
    //Serialize
    QVariantMap serialize() const;

    //Self
    int getId() const;
    Container * getParent() const;

    void setUserData(int userData);
    qintptr getUserData() const;

    void setClassIndex(ElementClass classIndex);
    ElementClass getClassIndex();

    void setFlags(const ElementFlgs &flags);
    ElementFlags getFlags() const;

    void setGroup(int group);
    int getGroup() const;

    void setLinkIs(bool linkIs);
    bool getLinkIs() const;

    void setLinkMain(qintptr linkMain);
    qintptr getLinkMain() const;

    void setPosX(int posX);
    int getPosX() const;

    void setPosY(int posY);
    int getPosY() const;

    void setSizeW(int sizeW);
    int getSizeW() const;

    void setSizeH(int sizeH);
    int getSizeH() const;

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
    PCodeGenTools getCgt();

    //Model
    SceneModel * getModel();

    //Container
    int getCountContainers() const;
    Container * getContainer() const;
    int getIdContainer() const;
    Container * getContainerByIndex(int index) const;
    int getIdContainerByIndex(int index) const;
    Container * addContainer(Container * container);
    void removeContainer(int index);

    //Point
    int getCountPoints() const;
    int getPointIndexOfType(const Point *id_point) const;
    Point * getPointByIndex(int index) const;
    Point * getIdPointByIndex(int index) const;
    Point * getPointByName(const QString &name) const;
    Point * getIdPointByName(const QString &name) const;
    Point * addPoint(Point * point);
    void removePoint(int index);

    //Property
    int getCountProps() const;
    Property * getPropertyByIndex(int index) const;
    Property * getIdPropertyByIndex(int index) const;
    Property * getPropertyById(Property * id_prop) const;
    Property * getPropertyByName(const QString &name) const;
    Property * getIdPropertyByName(const QString &name) const;
    Property * addProperty(Property * property);
    void removeProperty(int index);
};
