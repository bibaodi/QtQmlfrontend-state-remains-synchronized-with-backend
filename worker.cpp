#include "worker.h"
#include <QDebug>
#include <QGuiApplication>

#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QThread>

Worker::Worker() : QObject(nullptr), isRunning(false) {}

void Worker::doWork() {
  static int workid = 0;
  qDebug() << "task id=" << workid++;
  // QMutexLocker locker(&mutex);
  if (isRunning) {
    qDebug() << "Previous task is still running.(without mutex also work--eton@250707)";
    return;
  }
  //--
  m_wkthread = new QThread(this);
  QObject::connect(m_wkthread, &QThread::started, [this]() {
    // Simulate a long-running task
    int NN = 5;
    while (--NN > 0) {
      QThread::sleep(1);
      qDebug() << "working timer=" << NN;
    }
    emit workFinished(true);
    m_wkthread->quit();
  });
  QObject::connect(m_wkthread, &QThread::finished, m_wkthread, &QThread::deleteLater);
  QObject::connect(this, &Worker::workFinished, [this]() {
    // Handle work finished signal if needed
    qDebug() << "Handle work finished signal if needed";
    isRunning = false;
  });
  isRunning = true;
  emit workStarted();
  m_wkthread->start();
  //--
#if 0
    // Simulate a long-running task
     QThread::sleep(5);//this will cause GUI cannot update.
#endif
}
