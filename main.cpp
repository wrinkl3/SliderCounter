#include "mainwindow.h"
#include <QApplication>
#include <QVBoxLayout>
#include <QLabel>
#include <ctkrangeslider.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}
