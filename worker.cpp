#include "worker.h"
#include <QThread>
#include <QList>
#include <QString>

Worker::Worker(QObject *parent) :
    QObject(parent)
{

}

void Worker::requestWork(const QList<double> &list, const int low, const int high)
{
    this->list = list;
    this->high = high;
    this->low = low;
    emit workRequested();
}

void Worker::doWork()
{
    double sum = 0;
    for(int i = low; i<high; i++){
        sum+=list[i];
    }
    QThread::msleep(250);
    emit resultReady(QString::number(sum));
    emit finished();
}
