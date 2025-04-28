#include "dichotomytests.h"
#include "../echoServer/dichotomymethod.h"

Task3Tests::Task3Tests()
{
}

QByteArray task3(QString func, QString left, QString right, QString epsilon, QString maxIter)
{
    double left_val = left.toDouble();
    double right_val = right.toDouble();
    double epsilon_val = epsilon.toDouble();
    int maxIter_val = maxIter.toInt();
    //qDebug() << func;
    try {
        DichotomyMethod bisecMethod(func, left_val, right_val, epsilon_val, maxIter_val);
        double result = bisecMethod.solve();
        return QByteArray::number(result);
    } catch (const std::runtime_error &e) {
        return QByteArray("Error: ") + e.what() + "\n";
    }
}

void Task3Tests::testCase1() {
    QString func = "x*x - 4"; // x^2 - 4
    QString left = "0";
    QString right = "3";
    QString epsilon = "0.01";
    QString maxIter = "100";
    QVERIFY(qAbs(task3(func, left, right, epsilon, maxIter).toDouble() - 2.0) < 0.01);
}

void Task3Tests::testCase2() {
    QString func = "x*x*x - 1"; // x^3 - 1
    QString left = "0";
    QString right = "2";
    QString epsilon = "0.1";
    QString maxIter = "100";
    QVERIFY(qAbs(task3(func, left, right, epsilon, maxIter).toDouble() - 1.0) < 0.1);
}

void Task3Tests::testCase3() {
    QString func = "x*x*x - 3*x + 2"; // x^3 - 3*x + 2
    QString left = "0";
    QString right = "2";
    QString epsilon = "0.1";
    QString maxIter = "100";
    QVERIFY(qAbs(task3(func, left, right, epsilon, maxIter).toDouble() - 1.0) < 0.1);
}

void Task3Tests::testCase4() {
    QString func = "x/2 - 1"; // Пример деления
    QString left = "1";
    QString right = "5";
    QString epsilon = "0.01";
    QString maxIter = "100";
     QVERIFY(qAbs(task3(func, left, right, epsilon, maxIter).toDouble() - 2.0) < 0.01);
}

void Task3Tests::testCase5() {
    QString func = "(x + 4) - 2"; // x - 2
    QString left = "-7";
    QString right = "7";
    QString epsilon = "0.01";
    QString maxIter = "100";
    QVERIFY(qAbs(task3(func, left, right, epsilon, maxIter).toDouble() - (-2.0)) < 0.01);
}

void Task3Tests::testCase6() {
    QString func = "x*x - 1"; // x^2 - 1
    QString left = "-2";
    QString right = "0";
    QString epsilon = "0.001";
    QString maxIter = "10000";
    QVERIFY(qAbs(task3(func, left, right, epsilon, maxIter).toDouble() - (-1.0)) < 0.0001);
}
