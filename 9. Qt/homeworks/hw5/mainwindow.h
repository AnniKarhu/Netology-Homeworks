#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "stopwatch.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow(); 

private slots:

    void btnStartStop_clicked();
    void btnClear_clicked();
    void btnLap_clicked();
    void on_timer();

private:
    const int timer_interval = 100;
    Ui::MainWindow *ui;
    QTimer* timer;
    Stopwatch _stopwatch;
};
#endif // MAINWINDOW_H
