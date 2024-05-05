#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "dialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dialogWindow = new Dialog(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_open_DB_Connect_window_clicked()
{
    dialogWindow->show();
}

