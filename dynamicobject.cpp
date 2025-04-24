#include "dynamicobject.h"

#include "dynamicobject.h"
#include <QDebug>

DynamicObject::DynamicObject(QObject *parent) : QObject(parent) {
  initMetaObject();
}

void DynamicObject::initMetaObject() {
  QMetaObjectBuilder builder;
  builder.setClassName("DynamicObject");
  builder.setSuperClass(&QObject::staticMetaObject);

  // Добавим метод sayHello(QString)
  builder.addMethod("sayHello(QString)");
  methodCallbacks.append([](void **args) {
    QString arg = *reinterpret_cast<QString *>(args[1]);
    qDebug() << "Привет из динамического слота:" << arg;
  });

  dynamicMetaObject = builder.toMetaObject();
}

const QMetaObject *DynamicObject::metaObject() const {
  return dynamicMetaObject ? dynamicMetaObject : QObject::metaObject();
}

int DynamicObject::qt_metacall(QMetaObject::Call call, int id, void **args) {
  id = QObject::qt_metacall(call, id, args);
  if (id < 0 || call != QMetaObject::InvokeMetaMethod)
    return id;

  if (id < methodCallbacks.size()) {
    methodCallbacks[id](args);
    return -1;
  }

  return id;
}
