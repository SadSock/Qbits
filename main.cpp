#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <f64rawdata.h>
#include <e5m2rawdata.h>

int main(int argc, char *argv[])
  {
  QGuiApplication app(argc, argv);
  //qmlRegisterType<CppObject>("MyObjects", 1, 0, "MyObject");
  QQmlApplicationEngine engine;
  F64RawData m_f64RawData;
  E5m2RawData m_e5m2RawData;
  QQmlContext *qmlctx = engine.rootContext();
  qmlctx->setContextProperty("f64rawdatas",&m_f64RawData);
  qmlctx->setContextProperty("e5m2rawdatas",&m_e5m2RawData);
  const QUrl url(u"qrc:/Qbits/Main.qml"_qs);
  QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
      &app, []() { QCoreApplication::exit(-1); },
      Qt::QueuedConnection);
  engine.load(url);

  return app.exec();
  }
