#ifndef WORKER_H
#define WORKER_H

#include <QMutex>
#include <QObject>
#include <QSharedPointer>

class Worker : public QObject {
  Q_OBJECT
public:
  Worker();
  ~Worker();

public slots:
  void doWork();
  void doWorkSync();
  void doWorkWithNewThread();

signals:
  void workStarted();
  void workFinished(bool success);

private:
  int prepareThread();
  QMutex mutex;
  bool isRunning;
  QSharedPointer<QThread> m_wkthread;
  QSharedPointer<QThread> m_OnetimeThread{nullptr};
};

#endif // WORKER_H
