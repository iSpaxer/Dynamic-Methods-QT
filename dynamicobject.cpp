#include "dynamicobject.h"

#include "dynamicobject.h"
#include <QDebug>

void InnerObject::printMessage(QString msg) {
  qDebug() << "Слот printMessage получил:" << msg;
  emit somethingHappened(msg);
}

DynamicObject::DynamicObject(QObject *parent)
    : QObject(parent), _impl(new InnerObject(this)) {
  initMeta();
}

void DynamicObject::initMeta() {
  QMetaObjectBuilder builder;
  builder.setClassName("DynamicObject");
  builder.setSuperClass(&QObject::staticMetaObject);

  builder.addSlot("dynamicHello(QString)");
  methodCallbacks.append([](void **args) {
    QString arg = *reinterpret_cast<QString *>(args[1]);
    qDebug() << "Dynamic слот вызван с аргументом:" << arg;
  });

  dynamicMeta = builder.toMetaObject();
}

const QMetaObject *DynamicObject::metaObject() const {
  return dynamicMeta ? dynamicMeta : QObject::metaObject();
}


int DynamicObject::qt_metacall(QMetaObject::Call call, int id, void **args) {
    // Обработаем методы через динамический metaObject
    id = QObject::qt_metacall(call, id, args);

    if (id < 0 || call != QMetaObject::InvokeMetaMethod)
        return id;

    if (id < methodCallbacks.size()) {
        methodCallbacks[id](args);
        return -1;
    }

    return id;
}
