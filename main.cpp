#include "dynamicobject.h"
#include "qdebug.h"
#include <QCoreApplication>

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);

  DynamicObject obj;

  // Пробуем вызвать встроенный слот
  QMetaObject::invokeMethod(obj.impl(), "printMessage",
                            Q_ARG(QString, "Привет от обычного слота!"));

  // Пробуем динамический
  QMetaObject::invokeMethod(&obj, "dynamicHello",
                            Q_ARG(QString, "Привет от динамики!"));

  // Пробуем сигнал и слот
  QObject::connect(obj.impl(), &InnerObject::somethingHappened,
                   [](const QString &msg) {
                     qDebug() << "Слот на сигнал что-то получил:" << msg;
                   });

  // вызовем слот, он эмиттит сигнал
  obj.impl()->printMessage("И сигнал сработал");

  return a.exec();
}
