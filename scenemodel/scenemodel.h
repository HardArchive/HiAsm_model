#pragma once

//Project
#include "cgt/CGTShare.h"
#include "property.h"

//STL

//Qt
#include <QObject>
#include <QSet>

class Container;
class Element;

class SceneModel : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(SceneModel)

private:
    //CGT
    PCodeGenTools m_cgt{};

    //Map
    QMap<qint32, Container *> m_mapContainers;
    QMap<qint32, Element *> m_mapElements;

    //Container
    Container *m_container{};

    //Resource
    const QString m_resourcesDir = "resources";
    QSet<QString> m_resourcesToDelete;
    QMap<QString, QString> m_resourcesForCompile;

    //Параметры CGT
    bool m_isDebug{};
    qint32 m_debugMode = 0;
    qint32 m_debugServerPort = 120;
    qint32 m_debugClientPort = 121;
    qint32 m_sdeWidth = 0;
    qint32 m_sdeHeight = 0;
    QString m_hiasmVersion = "4.5.186";
    QString m_userName;
    QString m_userMail;
    QString m_codePath;
    QString m_projectPath;
    QString m_projectName;
    QString m_compiler;

private:
    Q_PROPERTY(PCodeGenTools cgt READ getCgt)
    Q_PROPERTY(SceneModel *model READ getModel)

public:
    explicit SceneModel(QObject *parent = 0);
    virtual ~SceneModel();

private:
    void collectingData(qint32 id_sdk);

public:
    qint32 genId()
    {
        return 0;
    }

    //Serialization
    QJsonDocument serialize();

    //CGT
    PCodeGenTools getCgt();

    //Model
    SceneModel *getModel();
    void initFromCgt(PCodeGenTools cgt, qint32 idMainSDK);
    bool saveModel(const QString &filePath);

    //Map
    void addContainerToMap(Container *id_sdk);
    void addElementToMap(Element *id_element);

    //Container
    Container *getContainerById(qint32 id_sdk) const;
    qint32 getCountElementsInContainer(qint32 id_sdk) const;
    qint32 getIdRootContainer() const;
    void setRootContainer(Container *container);

    //Element
    Element *getElementById(qint32 id_element) const;
    Element *getElementFromSDKByIndex(qint32 id_sdk, qint32 index) const;
    qint32 getIdElementFromSDKByIndex(qint32 id_sdk, qint32 index) const;

    //Resource
    const char *addStreamRes(Property *id_prop);
    const char *addStringRes(const QString &str);
    void deleteResources();
    void compileResources();

    qint32 addResList(const QString &filePath);
    bool resIsEmpty() const;

    //Параметры CGT
    void getCgtParam(CgtParams index, void *buf) const;

    bool getIsDebug() const;
    void setIsDebug(bool isDebug);

    qint32 getDebugMode() const;
    void setDebugMode(qint32 debugMode);

    qint32 getDebugServerPort() const;
    void setDebugServerPort(qint32 debugServerPort);

    qint32 getDebugClientPort() const;
    void setDebugClientPort(qint32 debugClientPort);

    qint32 getSdeWidth() const;
    void setSdeWidth(qint32 sdeWidth);

    qint32 getSdeHeight() const;
    void setSdeHeight(qint32 sdeHeight);

    QString getCodePath() const;
    void setCodePath(const QString &codePath);

    QString getProjectPath() const;
    void setProjectPath(const QString &projectPath);

    QString getHiasmVersion() const;
    void setHiasmVersion(const QString &hiasmVersion);

    QString getUserName() const;
    void setUserName(const QString &userName);

    QString getUserMail() const;
    void setUserMail(const QString &userMail);

    QString getProjectName() const;
    void setProjectName(const QString &projectName);

    QString getCompiler() const;
    void setCompiler(const QString &compiler);
};

Q_DECLARE_METATYPE(SceneModel *)
