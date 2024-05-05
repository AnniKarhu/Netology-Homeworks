#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_open_DB_Connect_window_clicked();

private:
    Ui::MainWindow *ui;
    Dialog* dialogWindow;
};

#endif // MAINWINDOW_H
