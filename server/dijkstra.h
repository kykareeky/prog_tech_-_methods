#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <QMap>
#include <QVector>
#include <QSet>
#include <QString>
#include <QPair>
#include <QList>

class Graph {
  public:
    Graph();
    void addEdge(int from, int to, int weight = 1);
    QString dijkstra(int start, int end);

  private:
    QMap<int, QList<QPair<int, int>>> adjList; // node -> list of (neighbor, weight)
};

#endif // DIJKSTRA_H
