#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <f64rawdata.h>


int main(int argc, char *argv[])
  {
  QGuiApplication app(argc, argv);
  //qmlRegisterType<CppObject>("MyObjects", 1, 0, "MyObject");
  QQmlApplicationEngine engine;
  F64RawData m_f64RawData;
  QQmlContext *qmlctx = engine.rootContext();
  qmlctx->setContextProperty("f64rawdatas",&m_f64RawData);
  const QUrl url(u"qrc:/Qbits/Main.qml"_qs);
  QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
      &app, []() { QCoreApplication::exit(-1); },
      Qt::QueuedConnection);
  engine.load(url);

  return app.exec();
  }
