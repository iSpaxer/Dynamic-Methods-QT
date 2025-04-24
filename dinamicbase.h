#ifndef DINAMICBASE_H
#define DINAMICBASE_H

#pragma once

#include <QObject>
#include <QString>
#include <QVector>
#include <functional>

class DynamicBase : public QObject {
public:
  explicit DynamicBase(QObject *parent = nullptr);

protected:
  const QMetaObject *metaObject() const override {
    return dynamicMeta ? dynamicMeta : QObject::metaObject();
  }

  int qt_metacall(QMetaObject::Call call, int id, void **args) override;

  QVector<std::function<void(void **)>> methodCallbacks;
  const QMetaObject *dynamicMeta = nullptr;

  void initDynamicMetaObject(); // вынос генерации
};

#endif // DINAMICBASE_H
