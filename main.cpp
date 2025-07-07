#include <QGuiApplication>
#include <QQmlApplicationEngine>

//--
#include <QDebug>
#include <QGuiApplication>
#include <QMutex>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QThread>

#include "worker.h"

#include <filesystem>
#include <string>
#include <unistd.h>

void printThreads() {
  // Linux-specific code
  std::string procDir = "/proc/" + std::to_string(getpid()) + "/task";
  qDebug() << "procDir=" << procDir;
  int thCnt = 0;
  for (const auto &entry : std::filesystem::directory_iterator(procDir)) {
    qDebug() << thCnt++ << "]Thread ID:" << entry.path().filename().c_str();
  }
}

int main(int argc, char *argv[]) {
  QGuiApplication app(argc, argv);

  QQmlApplicationEngine engine;

  // Register the Worker type to make it available in QML
  qmlRegisterType<Worker>("an.example", 1, 0, "Worker");

  // Set the initial context property for the worker
  Worker worker;
  engine.rootContext()->setContextProperty(QStringLiteral("worker"), &worker);

  QObject::connect(
      &engine, &QQmlApplicationEngine::objectCreationFailed, &app, []() { QCoreApplication::exit(-1); }, Qt::QueuedConnection);
  engine.loadFromModule("frontend-state-remains-synchronized-with-backend", "Main");
  if (engine.rootObjects().isEmpty()) {
    return -1;
  }

  printThreads();

  return app.exec();
}
