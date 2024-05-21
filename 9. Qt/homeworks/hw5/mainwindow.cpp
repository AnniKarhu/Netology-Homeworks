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

    _stopwatch = new Stopwatch(ui->lblCurrentTimeValue);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete _stopwatch;
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
}

void MainWindow::btnLap_clicked()
{
    QString temp_str = _stopwatch->get_lap_time().toString("hh:mm:ss:zzz");
    ui->txtbrwsr_LapsInfo->append(temp_str);
}
