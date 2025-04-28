#include <QtTest>
#include "../dijkstra.h"

class TestDijkstra : public QObject
{
    Q_OBJECT

private slots:
    void testSimpleGraph()
    {
        Graph g;
        g.addEdge(1, 2, 1);
        g.addEdge(2, 3, 1);
        
        QString path = g.dijkstra(1, 3);
        QCOMPARE(path, QString("1 -> 2 -> 3"));
    }
    
    void testNoPath()
    {
        Graph g;
        g.addEdge(1, 2, 1);
        g.addEdge(3, 4, 1);
        
        QString path = g.dijkstra(1, 4);
        QCOMPARE(path, QString("No path found"));
    }
    
    void testWeightedGraph()
    {
        Graph g;
        g.addEdge(1, 2, 1);
        g.addEdge(2, 3, 5);
        g.addEdge(1, 3, 3);
        
        QString path = g.dijkstra(1, 3);
        QCOMPARE(path, QString("1 -> 3"));
    }
};

QTEST_APPLESS_MAIN(TestDijkstra)
#include "test_dijkstra.moc"
