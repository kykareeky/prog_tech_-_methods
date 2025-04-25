#include "dichotomymethod.h"
#include <QtMath>
#include <cmath>
#include <stdexcept>

DichotomyMethod::DichotomyMethod(const QString &function, double left, double right, double epsilon, int maxIter)
    : function(function), left(left), right(right), epsilon(epsilon), maxIter(maxIter) {}

double DichotomyMethod::solve()
{
    std::function<double(double)> f = parseFunction(function);

    double f_left = f(left);
    double f_right = f(right);
    if (abs(f_left) < epsilon) return left;
    if (abs(f_right) < epsilon) return right;

    int iter = 0;
    while (iter < maxIter) {
        double x = (left + right) / 2;
        double f_x = f(x);
        if (abs(f_x) < epsilon) return x;
        if (f_left < 0)
            f_x > 0 ? right = x : left = x;
        else f_x < 0 ? right = x : left = x;
        ++iter;
    }
    throw std::runtime_error("Max iterations reached without convergence");
}

std::function<double(double)> DichotomyMethod::parseFunction(const QString &function)
{
    return [function, this](double x) -> double {
        QString expr = function;
        expr.replace(" ","");
        expr.replace("x", QString::number(x));
        int pos = 0;
        return parseExpression(expr, pos);
    };
}

double DichotomyMethod::parseExpression(const QString &expression, int &pos)
{
    double result = parseTerm(expression, pos);

    while (pos < expression.length()) {
        QChar op = expression[pos];
        if (op == '+' || op == '-') {
            ++pos;
            double term = parseTerm(expression, pos);
            if (op == '+') {
                result += term;
            } else {
                result -= term;
            }
        } else {
            break;
        }
    }

    return result;
}

double DichotomyMethod::parseTerm(const QString &expression, int &pos)
{
    double result = parseFactor(expression, pos);

    while (pos < expression.length()) {
        QChar op = expression[pos];
        if (op == '*' || op == '/') {
            ++pos;
            double factor = parseFactor(expression, pos);
            if (op == '*') {
                result *= factor;
            } else {
                result /= factor;
            }
        } else {
            break;
        }
    }

    return result;
}

double DichotomyMethod::parseFactor(const QString &expression, int &pos)
{
    double result;
    bool negative = false;

    if (expression[pos] == '-') {
        negative = true;
        ++pos;
    }

    if (expression[pos] == '(') {
        ++pos; // Skip '('
        result = parseExpression(expression, pos);
        if (expression[pos] == ')') {
            ++pos; // Skip ')'
        }
    } else {
        int startPos = pos;
        while (pos < expression.length() && (expression[pos].isDigit() || expression[pos] == '.')) {
            ++pos;
        }
        result = expression.mid(startPos, pos - startPos).toDouble();
    }

    if (negative) {
        result = -result;
    }

    return result;
}
