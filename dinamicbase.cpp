#include "dinamicbase.h"

#include <QDebug>

#include <private/qmetaobjectbuilder_p.h>

DynamicBase::DynamicBase(QObject *parent) : QObject(parent) {
  initDynamicMetaObject();
}

void DynamicBase::initDynamicMetaObject() {
  // Эмуляция JSON
  struct JsonMethod {
    QString name;
    QString signature;
    std::function<void(void **)> callback;
  };

  QVector<JsonMethod> jsonMethods = {
      {"sayHello", "sayHello(QString)", [](void **args) {
         QString arg = *reinterpret_cast<QString *>(args[1]);
         qDebug() << "Привет из JSON:" << arg;
       }}};

  // Создаём metaobject
  QMetaObjectBuilder builder;
  builder.setClassName("DynamicBase");
  builder.setSuperClass(&QObject::staticMetaObject);

  for (const auto &m : jsonMethods) {
    builder.addMethod(m.signature.toUtf8());
    methodCallbacks.append(m.callback);
  }

  dynamicMeta = builder.toMetaObject();
  *reinterpret_cast<const QMetaObject **>(this) = dynamicMeta;
}

int DynamicBase::qt_metacall(QMetaObject::Call call, int id, void **args) {
  id = QObject::qt_metacall(call, id, args);
  if (id < 0)
    return id;

  if (call == QMetaObject::InvokeMetaMethod) {
    if (id < methodCallbacks.size()) {
      methodCallbacks[id](args);
      return -1;
    }
  }

  return id;
}
