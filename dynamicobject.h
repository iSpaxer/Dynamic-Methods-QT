#ifndef DYNAMICOBJECT_H
#define DYNAMICOBJECT_H

#include "dinamicbase.h"
#include <QObject>
#include <private/qmetaobjectbuilder_p.h>
// dynamicobject.h
#pragma once

#pragma once

#include <QMetaObject>
#include <QObject>
#include <QVector>
#include <functional>

class DynamicObject : public QObject {
public:
  explicit DynamicObject(QObject *parent = nullptr);

  const QMetaObject *metaObject() const override;
  int qt_metacall(QMetaObject::Call call, int id, void **args) override;

private:
  QVector<std::function<void(void **)>> methodCallbacks;
  const QMetaObject *dynamicMetaObject = nullptr;

  void initMetaObject();
};
#endif // DYNAMICOBJECT_H
