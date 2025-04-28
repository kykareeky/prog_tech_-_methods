#include <QCoreApplication>
#include "database.h"
#include "tcpserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv); // create terminal
    DataBase& dbInstance = DataBase::getInstance();
    TcpServer myserv;
    return a.exec();
}
