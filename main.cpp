#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <e11m53rawdata.h>
#include <e5m2rawdata.h>
#include <e4m3rawdata.h>

int main(int argc, char *argv[])
  {
  QGuiApplication app(argc, argv);
  //qmlRegisterType<CppObject>("MyObjects", 1, 0, "MyObject");
  QQmlApplicationEngine engine;
  E11m53RawData m_e11m54RawData;
  E5m2RawData m_e5m2RawData;
  E4m3RawData m_e4m3RawData;
  QQmlContext *qmlctx = engine.rootContext();
  qmlctx->setContextProperty("f64rawdatas",&m_e11m54RawData);
  qmlctx->setContextProperty("e5m2rawdatas",&m_e5m2RawData);
  qmlctx->setContextProperty("e4m3rawdatas",&m_e4m3RawData);
  const QUrl url(u"qrc:/Qbits/Main.qml"_qs);
  QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
      &app, []() { QCoreApplication::exit(-1); },
      Qt::QueuedConnection);
  engine.load(url);

  return app.exec();
  }
