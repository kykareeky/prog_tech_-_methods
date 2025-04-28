#include <QtTest>
#include "../functionsforserver.h"

class TestFunctionsForServer : public QObject
{
    Q_OBJECT

private slots:
    void init()
    {
        // Инициализация тестовой БД
        QFile::remove("test_functions.db");
        qputenv("DB_NAME", "test_functions.db");
        DataBase::getInstance().createTable();
    }
    
    void testAuthSuccess()
    {
        // Подготовка тестовых данных
        QSqlQuery query(DataBase::getInstance().getDatabase());
        query.prepare("INSERT INTO users (login, password, email, sockid) VALUES (?, ?, ?, ?)");
        query.addBindValue("test_user");
        query.addBindValue("test_pass");
        query.addBindValue("test@email.com");
        query.addBindValue(0);
        query.exec();
        
        // Тест
        QByteArray result = auth("test_user", "test_pass");
        QVERIFY(result.startsWith("auth"));
    }
    
    void testAuthFailure()
    {
        QByteArray result = auth("wrong_user", "wrong_pass");
        QVERIFY(result.startsWith("Error"));
    }
    
    void testTask1()
    {
        QByteArray result = task1("test message");
        QVERIFY(!result.isEmpty());
        QVERIFY(result.contains("200B")); // Проверка на наличие ZWSP
    }
    
    void testTask3()
    {
        QByteArray result = task3("x - 2", "0", "5", "0.001", "100");
        QVERIFY(result.contains("root"));
    }
    
    void cleanup()
    {
        QFile::remove("test_functions.db");
    }
};

QTEST_APPLESS_MAIN(TestFunctionsForServer)
#include "test_functionsforserver.moc"
