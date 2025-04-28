#include <QtTest>
#include "../database.h"

class TestDatabase : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase()
    {
        // Удаляем тестовую БД если существует
        QFile::remove("test_database.db");
        qputenv("DB_NAME", "test_database.db");
    }
    
    void testSingleton()
    {
        DataBase& instance1 = DataBase::getInstance();
        DataBase& instance2 = DataBase::getInstance();
        QVERIFY(&instance1 == &instance2);
    }
    
    void testCreateTable()
    {
        DataBase& db = DataBase::getInstance();
        QVERIFY(db.createTable());
        
        QSqlQuery query(db.getDatabase());
        QVERIFY(query.exec("SELECT * FROM users"));
    }
    
    void testAuth()
    {
        DataBase& db = DataBase::getInstance();
        QSqlQuery query(db.getDatabase());
        query.prepare("INSERT INTO users (login, password, email, sockid) VALUES (?, ?, ?, ?)");
        query.addBindValue("test_user");
        query.addBindValue("test_pass");
        query.addBindValue("test@email.com");
        query.addBindValue(0);
        QVERIFY(query.exec());
        
        QStringList authQuery;
        authQuery << "SELECT * FROM users WHERE login = :login AND password = :password"
                 << ":login" << "test_user"
                 << ":password" << "test_pass";
        
        QStringList result = db.queryToDatabase(authQuery);
        QVERIFY(result.contains("found"));
    }
    
    void cleanupTestCase()
    {
        QFile::remove("test_database.db");
    }
};

QTEST_APPLESS_MAIN(TestDatabase)
#include "test_database.moc"
