
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow main_window;
    main_window.show();
   // Dialog w;
   // w.show();
    return a.exec();
}
