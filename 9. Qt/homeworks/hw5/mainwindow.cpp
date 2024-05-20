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

    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, MainWindow::on_timer);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
}

void MainWindow::on_timer()
{

    QString total_time_str =  _stopwatch.get_total_time().toString("hh:mm:ss:zzz");
    ui->lblCurrentTimeValue->setText(total_time_str);

}


void MainWindow::btnStartStop_clicked()
{  
    if (timer->isActive())
    {
        QString total_time_str =  _stopwatch.get_total_time().toString("hh:mm:ss:zzz");
        timer->stop();
        ui->btnLap->setEnabled(false);
        ui->lblCurrentTimeValue->setText(total_time_str);
        ui->btnStartStop->setText("Старт");
       // qDebug() << "timer not active " << total_time_str;
    }
    else
    {
        ui->lblCurrentTimeValue->setText("0");
        _stopwatch.StartTimer();
        timer->start(timer_interval);
        ui->btnLap->setEnabled(true);
        ui->btnStartStop->setText("Стоп");
       // qDebug() << "timer active ";
    }

}

void  MainWindow::btnClear_clicked()
{
     ui->lblCurrentTimeValue->setText("0");
}

void MainWindow::btnLap_clicked()
{
    QString temp_str = _stopwatch.get_lap_time().toString("hh:mm:ss:zzz");
    ui->txtbrwsr_LapsInfo->append(temp_str);
}
