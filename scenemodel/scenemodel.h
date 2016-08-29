#pragma once

//Project
#include "cgt/CGTShare.h"
#include "package/packagemanager.h"
#include "types.h"
#include "value.h"

//STL

//Qt
#include <QObject>
#include <QSet>

class SceneModel : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY(SceneModel)

private:
    //CGT
    PCodeGenTools m_cgt{};

    //Model
    qintptr m_genId = 1;

    //Package
    PPackage m_package{};
    PPackageManager m_packageManager{};

    //Map
    MapContainers m_mapContainers;
    MapElements m_mapElements;
    MapProperties m_mapProperties;
    MapPoints m_mapPoints;
    MapValues m_mapValues;

    //Container
    PContainer m_container{};

    //Resource
    const QString m_resourcesDir = "resources";
    QSet<QString> m_resourcesToDelete;
    QMap<QString, QString> m_resourcesForCompile;

    //Параметры CGT
    bool m_isDebug{};
    int m_debugMode = false;
    int m_debugServerPort = 120;
    int m_debugClientPort = 121;
    int m_sdeWidth = 0;
    int m_sdeHeight = 0;
    QString m_hiasmVersion = "4.5.186";
    QString m_userName;
    QString m_userMail;
    QString m_codePath;
    QString m_projectPath;
    QString m_projectName;
    QString m_compiler;

private:
    Q_PROPERTY(PCodeGenTools cgt READ getCgt)
    Q_PROPERTY(PSceneModel model READ getModel)

public:
    explicit SceneModel(PPackageManager package, QObject *parent = 0);
    virtual ~SceneModel();

private:
    void collectingData(qintptr id_sdk);

public:
    //Serialization
    QJsonDocument serialize();
    void deserialize(const QJsonDocument &doc);

    //CGT
    PCodeGenTools getCgt();

    //Model
    qintptr genId();
    PSceneModel getModel();
    void initFromCgt(PCodeGenTools cgt, qintptr idMainSDK);
    bool saveModel(const QString &filePath);
    bool loadModel(const QString &filePath);
    bool loadFromSha(const QString &filePath);

    //Package
    void setPackage(PPackage package);
    PPackage getPackage();
    bool loadPackage(const QString &name);

    //Map
    void addContainerToMap(PContainer id_sdk);
    void addElementToMap(PElement id_element);
    void addPropertyToMap(PProperty id_prop);
    void addPointToMap(PPoint id_point);
    void addValueToMap(qintptr id, PValue value);

    //Container
    PContainer getContainerById(qintptr id_sdk) const;
    int getCountElementsInContainer(qintptr id_sdk) const;
    qintptr getIdRootContainer() const;

    //Element
    PElement getElementById(qintptr id_element) const;
    PElement getElementFromSDKByIndex(qintptr id_sdk, int index) const;
    qintptr getIdElementFromSDKByIndex(qintptr id_sdk, int index) const;

    //Property
    PProperty getPropertyById(qintptr id_prop) const;

    //Point
    PPoint getPointById(qintptr id_point) const;

    //Value
    PValue getValueById(qintptr id_value) const;

    //Resource
    const char *addStreamRes(qintptr id_prop);
    const char *addStringRes(const QString &str);
    void deleteResources();
    void compileResources();

    int addResList(const QString &filePath);
    bool resIsEmpty() const;

    //Параметры CGT
    void getCgtParam(CgtParams index, void *buf) const;

    bool getIsDebug() const;
    void setIsDebug(bool isDebug);

    int getDebugMode() const;
    void setDebugMode(int debugMode);

    int getDebugServerPort() const;
    void setDebugServerPort(int debugServerPort);

    int getDebugClientPort() const;
    void setDebugClientPort(int debugClientPort);

    int getSdeWidth() const;
    void setSdeWidth(int sdeWidth);

    int getSdeHeight() const;
    void setSdeHeight(int sdeHeight);

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

Q_DECLARE_METATYPE(PSceneModel)
