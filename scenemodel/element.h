#pragma once

//Project
#include "types.h"
#include "cgt/CGTShare.h"

//STL

//Qt
#include <QObject>
#include <QString>

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
    PSceneModel m_model{};

    //Container
    Containers m_containers;

    //Point
    Points m_points;

    //Property
    Properties m_properties;

private:
    Q_PROPERTY(PSceneModel model READ getModel)
    Q_PROPERTY(PCodeGenTools cgt READ getCgt)

public:
    explicit Element(const QString &name, qintptr id_element, int X, int Y, QObject *parent);
    explicit Element(qintptr id_element, QObject *parent);

private:
    void collectingData();

public:
    //Serialize
    QVariantMap serialize();

    //Self
    int getId() const;
    PContainer getParent() const;

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
    PSceneModel getModel();

    //Container
    int getCountContainers() const;
    PContainer getContainer() const;
    int getIdContainer() const;
    PContainer getContainerByIndex(int index);
    int getIdContainerByIndex(int index);
    PContainer addContainer(PContainer container);
    void removeContainer(int index);

    //Point
    int getCountPoints() const;
    int getPointIndexOfType(const Point *id_point) const;
    PPoint getPointByIndex(int index) const;
    PPoint getIdPointByIndex(int index) const;
    PPoint getPointByName(const QString &name) const;
    PPoint getIdPointByName(const QString &name) const;
    PPoint addPoint(PPoint point);
    void removePoint(int index);

    //Property
    int getCountProps() const;
    PProperty getPropertyByIndex(int index) const;
    PProperty getIdPropertyByIndex(int index) const;
    PProperty getPropertyById(PProperty id_prop) const;
    PProperty getPropertyByName(const QString &name) const;
    PProperty getIdPropertyByName(const QString &name) const;
    PProperty addProperty(PProperty property);
    void removeProperty(int index);
};
