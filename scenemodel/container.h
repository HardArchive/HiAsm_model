#pragma once

//Project
#include "cgt/CGTShare.h"

//STL

//Qt
#include <QObject>

class SceneModel;
class Element;

class Container : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Container)

private:
    //Self
    qint32 m_id{};
    QString m_name;

    //CGT
    TCodeGenTools *m_cgt{};

    //Model
    SceneModel *m_model{};

    //Element
    QVector<Element *> m_elements;

private:
    Q_PROPERTY(SceneModel *model READ getModel)
    Q_PROPERTY(TCodeGenTools *cgt READ getCgt)

public:
    explicit Container(qint32 id_sdk, QObject *parent);
    explicit Container(QObject *parent);

private:
    void collectingData();

public:
    //Serialize
    QVariantMap serialize() const;

    //Self
    qint32 getId() const;
    Element *getParent() const;
    void setName(const QString &name);
    QString getName() const;

    //CGT
    TCodeGenTools *getCgt();

    //Model
    SceneModel *getModel() const;

    //Element
    qint32 getCountElements() const;
    Element *getElementByIndex(qint32 index) const;
    qint32 getIdElementByIndex(qint32 index) const;
    Element *getElementByName(const QString &name) const;
    qint32 getIdElementByName(const QString &name) const;
    Element *addElement(Element *element);
    void removeElement(qint32 index);
};
