#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <QMap>
#include <QVector>
#include <QSet>
#include <QString>
#include <QPair>
#include <QList>

/**
 * @brief Класс для представления графа и поиска кратчайшего пути алгоритмом Дейкстры
 */
class Graph {
  public:
    /**
     * @brief Конструктор класса Graph
     */
    Graph();

    /**
     * @brief Добавляет ребро в граф
     * @param from Вершина-источник
     * @param to Вершина-назначение
     * @param weight Вес ребра (по умолчанию 1)
     */
    void addEdge(int from, int to, int weight = 1);

    /**
     * @brief Находит кратчайший путь от start до end с помощью алгоритма Дейкстры
     * @param start Стартовая вершина
     * @param end Конечная вершина
     * @return Строка с путем в формате "start -> ... -> end" или сообщение об ошибке
     */
    QString dijkstra(int start, int end);

  private:
    /**
     * @brief Список смежности графа
     * Хранит вершину и список пар (сосед, вес ребра)
     */
    QMap<int, QList<QPair<int, int>>> adjList;
};

#endif // DIJKSTRA_H
