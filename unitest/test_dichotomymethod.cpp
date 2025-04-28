#include <QtTest>
#include "../dichotomymethod.h"

class TestDichotomyMethod : public QObject
{
    Q_OBJECT

private slots:
    void testLinearFunction()
    {
        DichotomyMethod dm("x - 2", 0, 5, 0.001, 100);
        double result = dm.solve();
        QVERIFY(qAbs(result - 2.0) < 0.001);
    }
    
    void testQuadraticFunction()
    {
        DichotomyMethod dm("x^2 - 4", 0, 5, 0.001, 100);
        double result = dm.solve();
        QVERIFY(qAbs(result - 2.0) < 0.001);
    }
    
    void testNoRoot()
    {
        DichotomyMethod dm("x^2 + 1", 0, 5, 0.001, 100);
        QVERIFY_EXCEPTION_THROWN(dm.solve(), std::runtime_error);
    }
    
    void testParser()
    {
        DichotomyMethod dm("", 0, 0, 0, 0);
        std::function<double(double)> f = dm.parseFunction("2*x + 1");
        QCOMPARE(f(2), 5.0);
    }
};

QTEST_APPLESS_MAIN(TestDichotomyMethod)
#include "test_dichotomymethod.moc"
