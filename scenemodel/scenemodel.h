#pragma once

//Project
#include "cgt/CGTShare.h"
#include "package/packagemanager.h"
#include "property.h"

//STL

//Qt
#include <QObject>
#include <QSet>

class Container;
class Element;

class SceneModel : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY(SceneModel)

private:
    //CGT
    PCodeGenTools m_cgt{};

    //Package
    PPackage m_package{};
    PPackageManager m_packageManager{};

    //Map
    QMap<qintptr, Container *> m_mapContainers;
    QMap<qintptr, Element *> m_mapElements;

    //Container
    Container *m_container{};

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
    Q_PROPERTY(SceneModel *model READ getModel)

public:
    explicit SceneModel(PPackageManager package, QObject *parent = 0);
    virtual ~SceneModel();

private:
    void collectingData(qintptr id_sdk);

public:
    //Serialization
    QJsonDocument serialize();

    //CGT
    PCodeGenTools getCgt();

    //Model
    SceneModel *getModel();
    void initFromCgt(PCodeGenTools cgt, qintptr idMainSDK);
    bool saveModel(const QString &filePath);

    //Package
    void setPackage(PPackage package);
    PPackage getPackage();
    bool loadPackage(const QString &name);

    //Map
    void addContainerToMap(Container *id_sdk);
    void addElementToMap(Element *id_element);

    //Container
    Container *getContainerById(qintptr id_sdk) const;
    int getCountElementsInContainer(qintptr id_sdk) const;
    qintptr getIdRootContainer() const;

    //Element
    Element *getElementById(qintptr id_element) const;
    Element *getElementFromSDKByIndex(qintptr id_sdk, int index) const;
    qintptr getIdElementFromSDKByIndex(qintptr id_sdk, int index) const;

    //Resource
    const char *addStreamRes(Property *id_prop);
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

Q_DECLARE_METATYPE(SceneModel *)
