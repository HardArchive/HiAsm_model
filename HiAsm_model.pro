#-------------------------------------------------
#
# Project created by QtCreator 2016-08-26T10:45:44
#
#-------------------------------------------------

TEMPLATE = lib
QT += core
CONFIG += c++14 dll
TARGET = CodeGen

#ru Путь до пакетов HiAsm
HIASM_PACKAGES = "C:/Users/Admin/AppData/Roaming/HiAsm_AltBuild/Elements"

#DESTDIR += $$HIASM_PACKAGES/CNET
DESTDIR += $$HIASM_PACKAGES/delphi

#ru Подключаем SceneModel
DEFINES += MODEL PROXY_MODEL

#ru Подключаем PROXY_ORIGINAL
#DEFINES += PROXY_ORIGINAL

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

SOURCES += $$files($$PWD/"entry/*.cpp", true)
HEADERS += $$files($$PWD/"entry/*.h", true)
SOURCES += $$files($$PWD/"cgt/*.cpp", true)
HEADERS += $$files($$PWD/"cgt/*.h", true)
SOURCES += $$files($$PWD/"scenemodel/*.cpp", true)
HEADERS += $$files($$PWD/"scenemodel/*.h", true)
SOURCES += $$files($$PWD/"package/*.cpp", true)
HEADERS += $$files($$PWD/"package/*.h", true)

#Подключаем логгер
include($$PWD/logger/logger.pri)
