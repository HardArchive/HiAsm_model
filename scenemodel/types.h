#pragma once

//Project

//STL

//Qt
#include <QVector>
#include <QMap>

class Value;
typedef QVector<Value *> Values;

class Property;
typedef QVector<Property *> Properties;

class Point;
typedef QVector<Point *> Points;

class Element;
typedef QVector<Element *> Elements;
typedef QMap<qintptr, Element *> MapElements;

class Container;
typedef QVector<Container *> Containers;
typedef QMap<qintptr, Container *> MapContainers;

class SceneModel;
typedef SceneModel *PSceneModel;
