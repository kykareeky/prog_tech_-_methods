#include "dijkstra.h"
#include <QStack>
#include <limits>

Graph::Graph() {}

/**
 * @brief Добавляет ребро между двумя вершинами в графе
 * @param from Вершина-источник
 * @param to Вершина-назначение
 * @param weight Вес ребра
 */
void Graph::addEdge(int from, int to, int weight) {
    adjList[from].append(qMakePair(to, weight));
    // Раскомментировать нижнюю строку, если хотим неориентированный граф
    adjList[to].append(qMakePair(from, weight));
}

/**
 * @brief Реализация алгоритма Дейкстры для поиска кратчайшего пути
 * @param start Начальная вершина
 * @param end Конечная вершина
 * @return Строка с путем в формате "start -> ... -> end" или сообщение "No path found"
 */
QString Graph::dijkstra(int start, int end) {
    QMap<int, int> dist; ///< Расстояние от старта до вершины
    QMap<int, int> prev; ///< Предыдущая вершина на кратчайшем пути
    QSet<int> allNodes; ///< Множество всех вершин

    // Добавим вершины из списка рёбер
    for (auto from : adjList.keys()) {
        allNodes.insert(from);
        for (const auto& pair : adjList[from]) {
            allNodes.insert(pair.first);
        }
    }

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
        // Теперь возвращаем сообщение с номерами вершин
        return QString("No path from %1 to %2").arg(start).arg(end);
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

    // Добавляем длину пути
    result += QString(" (длина %1)").arg(dist[end]);

    return result;
}
