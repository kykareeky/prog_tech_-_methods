#ifndef DATABASE_H
#define DATABASE_H

#include <QCoreApplication>
#include <QDebug>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QVariant>
#include <QStringList>

/**
 * @class DataBase
 * @brief Класс для работы с базой данных, реализующий паттерн одиночка.
 */
class DataBase;

/**
 * @class DatabaseDestroyer
 * @brief Класс для правильного уничтожения объекта DataBase.
 */
class DatabaseDestroyer
{
private:
    DataBase * p_instance; ///< Указатель на экземпляр DataBase.
public:
    /**
     * @brief Деструктор класса DatabaseDestroyer.
     */
    ~DatabaseDestroyer();

    /**
     * @brief Инициализирует указатель на экземпляр DataBase.
     * @param p Указатель на экземпляр DataBase.
     */
    void initialize(DataBase * p);
};

/**
 * @class DataBase
 * @brief Класс для работы с базой данных, реализующий паттерн одиночка.
 */
class DataBase {
private:
    static DataBase *p_instance; ///< Указатель на единственный экземпляр класса.
    static DatabaseDestroyer destroyer; ///< Экземпляр класса DatabaseDestroyer для уничтожения объекта.
    QSqlDatabase db; ///< Объект базы данных.

    /**
     * @brief Конструктор класса DataBase.
     */
    DataBase();

    /**
     * @brief Деструктор класса DataBase.
     */
    ~DataBase();

    /**
     * @brief Конструктор копирования удален.
     */
    DataBase(const DataBase&) = delete;

    /**
     * @brief Оператор присваивания удален.
     */
    void operator= (const DataBase&) = delete;

    /**
     * @brief Класс DatabaseDestroyer является дружественным для DataBase.
     */
    friend class DatabaseDestroyer;

public:
    /**
     * @brief Создает таблицу в базе данных.
     * @return Возвращает true в случае успешного создания таблицы, иначе false.
     */
    bool createTable();

    /**
     * @brief Возвращает единственный экземпляр класса DataBase.
     * @return Ссылка на экземпляр DataBase.
     */
    static DataBase& getInstance();

    /**
     * @brief Возвращает объект базы данных.
     * @return Ссылка на объект QSqlDatabase.
     */
    QSqlDatabase& getDatabase();

    /**
     * @brief Выполняет запрос к базе данных.
     * @param query Список строк с SQL-запросами.
     * @return Список строк с результатами выполнения запросов.
     */
    QStringList queryToDatabase(QStringList query);
};

#endif

