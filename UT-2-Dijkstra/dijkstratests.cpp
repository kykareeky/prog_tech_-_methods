#include "dijkstratests.h"
#include "../echoServer/dijkstra.h"  // Путь до твоего task4()

Task4Tests::Task4Tests()
{
}

QByteArray task4(QString text)
{
    QStringList parts = text.split(' ', Qt::SkipEmptyParts);
    if (parts.size() < 2)
        return "error";

    int start = parts[0].toInt();
    int end = parts[1].toInt();
    QStringList edges = parts.mid(2);

    Graph g;
    for (const QString& e : edges) {
        QStringList edgeAndWeight = e.split('=');
        QString edgePart = edgeAndWeight[0];
        int weight = 1;

        if (edgeAndWeight.size() == 2) {
            bool ok = false;
            int parsedWeight = edgeAndWeight[1].toInt(&ok);
            if (ok) {
                weight = parsedWeight;
            }
        }

        QStringList nodes = edgePart.split('*');
        if (nodes.size() != 2) continue;

        bool okFrom = false, okTo = false;
        int from = nodes[0].toInt(&okFrom);
        int to = nodes[1].toInt(&okTo);

        if (okFrom && okTo) {
            g.addEdge(from, to, weight);
        }
    }

    QString resultPath = g.dijkstra(start, end);
    return resultPath.toUtf8();
}

// Самые простые пути
void Task4Tests::testCase1()
{
    QString input = "1 2 1*2";
    QByteArray output = task4(input);
    QCOMPARE(QString(output), QString("1 -> 2 (длина 1)"));
}

void Task4Tests::testCase2()
{
    QString input = "1 3 1*2 2*3";
    QByteArray output = task4(input);
    QCOMPARE(QString(output), QString("1 -> 2 -> 3 (длина 2)"));
}

void Task4Tests::testCase3()
{
    QString input = "1 4 1*2 2*3 3*4";
    QByteArray output = task4(input);
    QCOMPARE(QString(output), QString("1 -> 2 -> 3 -> 4 (длина 3)"));
}

// Проверка веса рёбер (разные стоимости)
void Task4Tests::testCase4()
{
    QString input = "1 3 1*2=1 2*3=2 1*3=10";
    QByteArray output = task4(input);
    QCOMPARE(QString(output), QString("1 -> 2 -> 3 (длина 3)"));
}

void Task4Tests::testCase5()
{
    QString input = "1 5 1*2=5 2*5=5 1*3=1 3*4=1 4*5=1";
    QByteArray output = task4(input);
    QCOMPARE(QString(output), QString("1 -> 3 -> 4 -> 5 (длина 3)"));
}

// Ошибочные случаи
void Task4Tests::testCase6()
{
    QString input = "1 2";  // Нет рёбер
    QByteArray output = task4(input);
    QCOMPARE(QString(output), QString("No path from 1 to 2"));
}

void Task4Tests::testCase7()
{
    QString input = "1 1";  // Старт == Финиш
    QByteArray output = task4(input);
    QCOMPARE(QString(output), QString("1 (длина 0)"));
}

// Невозможный путь
void Task4Tests::testCase8()
{
    QString input = "1 3 1*2";  // 2 не соединён с 3
    QByteArray output = task4(input);
    QCOMPARE(QString(output), QString("No path from 1 to 3"));
}

// Более сложный граф
void Task4Tests::testCase9()
{
    QString input = "1 5 1*2=2 2*3=2 3*5=2 1*4=1 4*5=10";
    QByteArray output = task4(input);
    QCOMPARE(QString(output), QString("1 -> 2 -> 3 -> 5 (длина 6)"));
}

// Путь через прямую связь, хотя есть другие пути
void Task4Tests::testCase10()
{
    QString input = "1 3 1*2=5 2*3=5 1*3=2";
    QByteArray output = task4(input);
    QCOMPARE(QString(output), QString("1 -> 3 (длина 2)"));
}
