#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->rbtnR1->setText("Radio button 1");
    ui->rbtnR2->setText("Radio button 2");
    for (int i = 0; i < 5; ++i)
    {
       QString str = "Item " + QString::number(i);
       ui->cbxItems->addItem(str);
    }



    ui->btnButton->setText("New button name");
    ui->btnButton->setCheckable(true);
    connect(ui->btnButton, &QPushButton::clicked, this, MainWindow::onButtonclicked);

    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(10);
    ui->progressBar->setValue(0);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onButtonclicked()
{
    int Increment = ui->progressBar->maximum()/10;
    int newValue = ui->progressBar->value() + Increment;
    if (newValue > ui->progressBar->maximum())
    {
        newValue = ui->progressBar->minimum();
    }
    ui->progressBar->setValue(newValue);
    qDebug() << "q";
    return;
}
