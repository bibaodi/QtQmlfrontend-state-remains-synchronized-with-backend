#include "worker.h"
#include <QDebug>
#include <QGuiApplication>

#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QThread>

Worker::Worker() : QObject(nullptr), isRunning(false) {
  m_wkthread = QSharedPointer<QThread>(new QThread(this));
  prepareThread();
}

Worker::~Worker() {}

int Worker::prepareThread() {
  QObject::connect(m_wkthread.get(), &QThread::started, [this]() {
    // Simulate a long-running task
    int NN = 5;
    while (--NN > 0) {
      QThread::sleep(1);
      qDebug() << "working timer=" << NN;
    }
    emit workFinished(true);
    m_wkthread->quit();
  });
#if 0
//if   deleteLater invoked then thread must create again, otherwise this will crash for contents in thread alread deleted.--eton@250707
 QObject::connect(m_wkthread.get(), &QThread::finished, m_wkthread.get(), &QThread::deleteLater);
#endif
  QObject::connect(this, &Worker::workFinished, [this]() {
    // Handle work finished signal if needed
    qDebug() << "Handle work finished signal if needed";
    isRunning = false;
  });
  return 0;
}

void Worker::doWorkSync() {
  static int workid = 0;
  qDebug() << "task id=" << workid++;
  QMutexLocker locker(&mutex);
  if (isRunning) {
    qDebug() << "Previous task is still running.(without mutex also work--eton@250707)";
    return;
  }

  isRunning = true;
  emit workStarted();
  m_wkthread->start();

  // Simulate a long-running task
  QThread::sleep(5); // this will cause GUI cannot update.
  isRunning = false;
  emit workFinished(true);
}

void Worker::doWork() {
  static int workid = 0;
  qDebug() << "task id=" << workid++;
  // QMutexLocker locker(&mutex);
  if (isRunning) {
    qDebug() << "Previous task is still running.(without mutex also work--eton@250707)";
    return;
  }
  //--

  isRunning = true;
  emit workStarted();
  m_wkthread->start();
  //--
#if 0
    // Simulate a long-running task
     QThread::sleep(5);//this will cause GUI cannot update.
#endif
}

void Worker::doWorkWithNewThread() {
  static int workid = 0;
  qDebug() << "task id=" << workid++;
  if (isRunning) {
    qDebug() << "Previous task is still running.(without mutex also work--eton@250707)";
    return;
  }
  //--
  m_OnetimeThread = QSharedPointer<QThread>(new QThread(this));
  QObject::connect(m_OnetimeThread.get(), &QThread::started, [this]() {
    int NN = 3;
    while (--NN > 0) {
      QThread::sleep(1);
      qDebug() << "onetime working timer=" << NN;
    }
    emit workFinished(true);
    m_OnetimeThread->quit();
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
