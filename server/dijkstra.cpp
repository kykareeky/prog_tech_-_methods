#include "dijkstra.h"
#include <QStack>
#include <limits>

Graph::Graph() {}

void Graph::addEdge(int from, int to, int weight) {
    adjList[from].append(qMakePair(to, weight));
    // Раскомментировать нижнюю строку, если хотим неориентированный
    adjList[to].append(qMakePair(from, weight));
}

QString Graph::dijkstra(int start, int end) {
    QMap<int, int> dist;
    QMap<int, int> prev;
    QSet<int> allNodes;

           // Добавим вершины из списка рёбер
    for (auto from : adjList.keys()) {
        allNodes.insert(from);
        for (const auto& pair : adjList[from]) {
            allNodes.insert(pair.first);
        }
    }

           // Обязательно добавить start и end, даже если они не в рёбрах
    allNodes.insert(start);
    allNodes.insert(end);

    for (int node : allNodes) {
        dist[node] = std::numeric_limits<int>::max();
        prev[node] = -1;
    }

    dist[start] = 0;

    while (!allNodes.isEmpty()) {
        int minNode = -1;
        int minDist = std::numeric_limits<int>::max();

        for (int node : allNodes) {
            if (dist[node] < minDist) {
                minDist = dist[node];
                minNode = node;
            }
        }

               // 🔒 Нет доступных узлов — выйти
        if (minNode == -1 || dist[minNode] == std::numeric_limits<int>::max()) {
            break;
        }

        allNodes.remove(minNode);

        for (const QPair<int, int>& neighbor : adjList[minNode]) {
            int to = neighbor.first;
            int weight = neighbor.second;

            int alt = dist[minNode] + weight;
            if (alt < dist[to]) {
                dist[to] = alt;
                prev[to] = minNode;
            }
        }
    }

    if (dist[end] == std::numeric_limits<int>::max()) {
        return "No path found";
    }

           // Восстановим путь
    QStack<int> path;
    int current = end;
    while (current != -1) {
        path.push(current);
        current = prev[current];
    }

    QString result;
    while (!path.isEmpty()) {
        result += QString::number(path.pop());
        if (!path.isEmpty()) {
            result += " -> ";
        }
    }

    return result;
}

