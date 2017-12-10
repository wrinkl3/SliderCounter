#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ctkrangeslider.h"
#include "worker.h"
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QStringList>
#include <QtGui>
#include <QThread>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ctkRangeSlider *slider = ui->rangeSlider;
    readFile();
    int size = list.size();
    slider->setRange(0, size);
    slider->setMinimumPosition(0);
    slider->setMaximumPosition(size-1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
 * Read the csv file, parse it and keep it in-memory as a QList of doubles.
 * Assumes the file is properly formatted and cointains only doubles.
 */
void MainWindow::readFile(){
    QFile inputFile("/Users/Alex/SliderCounter/numbers.csv"); //change this

    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
          QString line = in.readLine();
          list << line.toDouble();

       }
       inputFile.close();
    }
}


void MainWindow::on_rangeSlider_valuesChanged(int low, int high)
{
    QThread *thread = new QThread();
    Worker *worker = new Worker();

    /*
     * Move the worker off-thread, ping-pong between the main
     * thread and the worker one and quit the worker thread
     * once the worker has signalled finish.
     */
    worker->moveToThread(thread);
    connect(worker, SIGNAL(resultReady(QString)), ui->sum_label, SLOT(setText(QString)));
    connect(worker, SIGNAL(workRequested()), thread, SLOT(start()));
    connect(thread, SIGNAL(started()), worker, SLOT(doWork()));
    connect(worker, SIGNAL(finished()), thread, SLOT(quit()), Qt::DirectConnection);
    worker->requestWork(list,low,high);
}
