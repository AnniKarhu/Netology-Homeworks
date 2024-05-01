#include <QCoreApplication>
#include <QSqlDatabase>
#include <QTcpSocket>

#include <iostream>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
        db.setHostName("acidalia");
        db.setDatabaseName("customdb");
        db.setUserName("mojito");
        db.setPassword("J0a1m8");
        bool ok = db.open();

    if (ok)
    {
        std::cout << "db opened" << std::endl;
    }
    else
    {
        std::cout << "db not opened" << std::endl;
    }


    auto socket = new QTcpSocket(nullptr);
    std::cout << socket->socketType() << std::endl;

    delete socket;

    return a.exec();
}
