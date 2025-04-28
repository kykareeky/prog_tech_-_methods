#ifndef DICHOTOMYTESTS_H
#define DICHOTOMYTESTS_H

#include <QObject>
#include <QTest>

class Task3Tests : public QObject
{
    Q_OBJECT
  public:
    Task3Tests();

  private slots:
    void testCase1();
    void testCase2();
    void testCase3();
    void testCase4();
    void testCase5();
    void testCase6();
};

#endif // DICHOTOMYTESTS_H
