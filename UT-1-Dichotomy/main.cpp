#include "dichotomytests.h"
#include <QCoreApplication>
#include <QTest>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    Task3Tests tests;
    return QTest::qExec(&tests, argc, argv);
}
