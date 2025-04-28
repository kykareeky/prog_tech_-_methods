#ifndef DICHOTOMYMETHOD_H
#define DICHOTOMYMETHOD_H

#include <QString>
#include <functional>

/**
 * @class DichotomyMethod
 * @brief Класс для метода дихотомии
 *
 * Этот класс реализует метод дихотомии (деление пополам)
 * для численного решения уравнений вида f(x) = 0.
 */
class DichotomyMethod
{
  public:
    /**
     * @brief Конструктор класса DichotomyMethod.
     *
     * @param function Строка, содержащая математическое выражение функции.
     * @param left Левая граница.
     * @param right Правая граница.
     * @param epsilon Точность решения.
     * @param maxIter Максимальное количество итераций.
     */
    DichotomyMethod(const QString &function, double left, double right, double epsilon, int maxIter);

    /**
     * @brief Решает уравнение методом дихотомии.
     *
     * @return Значение x, при котором f(x) приближается к нулю.
     *
     * @throws std::runtime_error Если не удается достичь необходимой точности за заданное количество итераций.
     */
    double solve();

  private:
    QString function; ///< Математическое выражение функции.
    double left; ///< Левая граница
    double right; ///< Правая граница
    double epsilon; ///< Точность решения.
    int maxIter; ///< Максимальное количество итераций.

    /**
     * @brief Вычисляет значение функции в точке x.
     *
     * @param x Значение аргумента, в котором вычисляется функция.
     * @return Значение функции в точке x.
     */
    double evaluateFunction(double x);

    /**
     * @brief Парсит строку с математическим выражением в функцию.
     *
     * @param function Строка с математическим выражением.
     * @return Функция, вычисляющая значение выражения.
     */
    std::function<double(double)> parseFunction(const QString &function);

    /**
     * @brief Парсит математическое выражение.
     *
     * @param expression Строка с математическим выражением.
     * @param pos Текущая позиция в строке.
     * @return Значение выражения.
     */
    double parseExpression(const QString &expression, int &pos);

    /**
     * @brief Парсит член математического выражения.
     *
     * @param expression Строка с математическим выражением.
     * @param pos Текущая позиция в строке.
     * @return Значение члена.
     */
    double parseTerm(const QString &expression, int &pos);

    /**
     * @brief Парсит множитель математического выражения.
     *
     * @param expression Строка с математическим выражением.
     * @param pos Текущая позиция в строке.
     * @return Значение множителя.
     */
    double parseFactor(const QString &expression, int &pos);
};

#endif // DICHOTOMYMETHOD_H
