#include <QCoreApplication>
#include <QTest>
#include "dijkstratests.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    Task4Tests tests;
    return QTest::qExec(&tests, argc, argv);
}
