#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->btnClear, &QPushButton::clicked, this, MainWindow::btnClear_clicked);
    connect(ui->btnStartStop, &QPushButton::clicked, this, MainWindow::btnStartStop_clicked);
    connect (ui->btnLap, &QPushButton::clicked, this, btnLap_clicked);

    _stopwatch = new Stopwatch();
    connect (_stopwatch, Stopwatch::on_timer_signal, this, MainWindow::on_timer);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete _stopwatch;
}

void MainWindow::on_timer(const QString& timer_time)
{
   ui->lblCurrentTimeValue->setText(timer_time);
}

void MainWindow::btnStartStop_clicked()
{  
    if ( _stopwatch->IsActive())
    {
        _stopwatch->StopTimer();
        ui->btnLap->setEnabled(false);
        ui->btnStartStop->setText("Старт");
    }
    else
    {
        _stopwatch->StartTimer();
        ui->btnLap->setEnabled(true);
        ui->btnStartStop->setText("Стоп");       
    }
}

void  MainWindow::btnClear_clicked()
{
     ui->lblCurrentTimeValue->setText("0");
     _stopwatch-> ClearTimer();
}

void MainWindow::btnLap_clicked()
{
   QString ResultStr = "Круг " +
            QString::number(_stopwatch->get_lap_num()) +
           ", время: " +
          _stopwatch->get_lap_time().toString("hh:mm:ss:zzz");

     ui->txtbrwsr_LapsInfo->append(ResultStr);
}
