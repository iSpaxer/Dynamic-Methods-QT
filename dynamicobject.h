#ifndef DYNAMICOBJECT_H
#define DYNAMICOBJECT_H

#include "dinamicbase.h"
#include <QObject>
#include <private/qmetaobjectbuilder_p.h>
// dynamicobject.h
#pragma once

#pragma once

#include <QObject>
#include <QVector>
#include <functional>

class InnerObject : public QObject {
  Q_OBJECT
public:
  using QObject::QObject;

signals:
  void somethingHappened(QString message);

public slots:
  void printMessage(QString msg);
};

class DynamicObject : public QObject {
public:
  explicit DynamicObject(QObject *parent = nullptr);

  const QMetaObject *metaObject() const override;
  int qt_metacall(QMetaObject::Call call, int id, void **args) override;

  // Доступ к сигналам
  InnerObject *impl() const { return _impl; }

private:
  void initMeta();

  QVector<std::function<void(void **)>> methodCallbacks;
  const QMetaObject *dynamicMeta = nullptr;
  InnerObject *_impl;
};
#endif // DYNAMICOBJECT_H
