#include "dynamicobject.h"
#include "qdebug.h"
#include <QCoreApplication>
#include <QMetaObject>

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);

  DynamicObject obj;

  bool ok = QMetaObject::invokeMethod(&obj, "sayHello", Q_ARG(QString, "Мир"));

  if (!ok) {
    qDebug() << "Не удалось вызвать метод";
  }

  return a.exec();
}
