#ifndef WORKER_H
#define WORKER_H

#include <QMutex>
#include <QObject>

class Worker : public QObject {
  Q_OBJECT
public:
  Worker();

public slots:
  void doWork();

signals:
  void workStarted();
  void workFinished(bool success);

private:
  QMutex mutex;
  bool isRunning;
  QThread *m_wkthread;
};

#endif // WORKER_H
