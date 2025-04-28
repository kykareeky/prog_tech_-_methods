#include <QCoreApplication>
#include <QTest>
#include "aestests.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    AESTests tests;
    return QTest::qExec(&tests, argc, argv);
}
