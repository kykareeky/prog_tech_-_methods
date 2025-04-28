#include <QtTest>
#include "test_database.h"
#include "test_dichotomymethod.h"
#include "test_dijkstra.h"
#include "test_functionsforserver.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    int status = 0;
    {
        TestDatabase test1;
        status |= QTest::qExec(&test1, argc, argv);
    }
    {
        TestDichotomyMethod test2;
        status |= QTest::qExec(&test2, argc, argv);
    }
    {
        TestDijkstra test3;
        status |= QTest::qExec(&test3, argc, argv);
    }
    {
        TestFunctionsForServer test4;
        status |= QTest::qExec(&test4, argc, argv);
    }
    
    return status;
}
