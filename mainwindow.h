#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    /*  keep the contents of the csv file in-memory */
    QList<double> list;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_rangeSlider_valuesChanged(int , int );

private:
    Ui::MainWindow *ui;
    void readFile();
};

#endif // MAINWINDOW_H
