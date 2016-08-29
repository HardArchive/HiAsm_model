﻿#pragma once

//Project

//STL

//Qt
#include <QVector>
#include <QMap>

class Value;
typedef Value *PValue;
typedef QMap<qintptr, PValue> MapValues;
typedef QVector<PValue> Values;

class Property;
typedef QMap<qintptr, Property *> MapProperties;
typedef QVector<Property *> Properties;

class Point;
typedef QVector<Point *> Points;
typedef QMap<qintptr, Point *> MapPoints;

class Element;
typedef Element *PElement;
typedef QVector<PElement> Elements;
typedef QMap<qintptr, PElement> MapElements;

class Container;
typedef Container *PContainer;
typedef QVector<PContainer> Containers;
typedef QMap<qintptr, PContainer> MapContainers;

class SceneModel;
typedef SceneModel *PSceneModel;
