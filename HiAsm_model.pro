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

SOURCES += \
    main.cpp

HEADERS +=
