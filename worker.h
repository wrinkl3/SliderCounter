#ifndef WORKER_H
#define WORKER_H

#include <QObject>

class Worker : public QObject
{
    Q_OBJECT

/*
 * This worker receives the data list and the current slider positions,
 * performs extremely expensive and complicated calculatations (sums a
 * bunch of doubles), waits for 250 ms, then signals the result.
 */
public:
    explicit Worker(QObject *parent = 0);
    void requestWork(const QList<double> &list, const int low, const int high);

private:
    QList<double> list;
    int high;
    int low;

signals:
    void workRequested();
    void resultReady(const QString &value);
    void finished();

public slots:
    void doWork();
};

#endif // WORKER_H
