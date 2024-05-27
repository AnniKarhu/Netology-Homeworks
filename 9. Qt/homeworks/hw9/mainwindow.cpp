#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    udpWorker = new UDPworker(this);
    udpWorker->InitSocket();

    connect(udpWorker, &UDPworker::sig_sendTimeToGUI, this, &MainWindow::DisplayTime);
    connect(udpWorker, &UDPworker::sig_sendText,      this, &MainWindow::DisplayTextString);


    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [&]{

        QDateTime dateTime = QDateTime::currentDateTime();

        QByteArray dataToSend;
        QDataStream outStr(&dataToSend, QIODevice::WriteOnly);

        outStr << dateTime;

        Data_to_Send data;
        data.data = dataToSend;
        data.dt_type = Data_Type::dt_time;

        udpWorker->SendData(data);

        timer->start(TIMER_DELAY);

    });

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_start_clicked()
{
    timer->start(TIMER_DELAY);
}

void MainWindow::on_btnSendText_clicked()
 {

     QString textStr = ui->edit_TextToSend->text();
     QByteArray dataToSend;

     //int len1 = textStr.length();
     //qDebug() << "длина строки length 1 = " << len1;
     //int len2 = sizeof(textStr);
     //qDebug() << "размер строковой переменной size 1 = " << len2;

     QDataStream outStr(&dataToSend, QIODevice::WriteOnly);

     outStr << textStr;

     Data_to_Send data;
     data.data = dataToSend;
     int len = dataToSend.length();
     qDebug() << "send length = " << len;
     //int len1 = dataToSend.size();
     //qDebug() << "send size = " << len;
     data.dt_type = Data_Type::dt_text;

     udpWorker->SendData(data);
 }


void MainWindow::DisplayTime(QDateTime data)
{
    counterPck++;
    if(counterPck % 20 == 0){
        ui->te_result->clear();
    }

    ui->te_result->append("Текущее время: " + data.toString() + ". "
                "Принято пакетов " + QString::number(counterPck));

}

void MainWindow::DisplayTextString(QString TextData, QString address, int data_length)
{
    counterPck++;
    if(counterPck % 20 == 0){
        ui->te_result->clear();
    }

    ui->te_result->append("Принято сообщение от " +
                          address + //адрес отправителя
                          ", размер сообщения(байт) " +
                          QString::number(data_length) +
                          ": " +
                          TextData + ". "
                "Принято пакетов " + QString::number(counterPck));
}



void MainWindow::on_pb_stop_clicked()
{
    timer->stop();
}

