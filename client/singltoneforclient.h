/**
 * @file Singltoneforclient.h
 * @brief Определение классов Singltoneforclient и SingltoneforclientDestroyer для создания Singleton объекта для работы с QTcpSocket.
 */

#ifndef SINGLTONEFORCLIENT_H
#define SINGLTONEFORCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QtNetwork>
#include <QByteArray>
#include <QDebug>

class Singltoneforclient;

/**
 * @class SingltoneforclientDestroyer
 * @brief Класс для уничтожения Singleton объекта Singltoneforclient.
 */
class SingltoneforclientDestroyer
{
  private:
    Singltoneforclient* p_instance; ///< Указатель на Singleton объект.

  public:
    /**
     * @brief Деструктор класса. Уничтожает Singleton объект.
     */
    ~SingltoneforclientDestroyer() { delete p_instance; }

    /**
     * @brief Инициализирует указатель на Singleton объект.
     * @param p Указатель на Singleton объект.
     */
    void initialize(Singltoneforclient* p) { p_instance = p; }

};

/**
 * @class Singltoneforclient
 * @brief Singleton класс для работы с QTcpSocket.
 */
class Singltoneforclient : public QObject
{
    Q_OBJECT

  private:
    static Singltoneforclient* p_instance; ///< Указатель на единственный экземпляр класса.
    static SingltoneforclientDestroyer destroyer; ///< Объект для уничтожения Singleton.
    QTcpSocket* mTcpSocket; ///< Указатель на QTcpSocket для взаимодействия с сервером.

  private slots:
    /**
     * @brief Слот для чтения данных от сервера.
     */
    void slotServerRead();

  protected:
    /**
     * @brief Конструктор класса.
     * @param parent Родительский объект.
     */
    explicit Singltoneforclient(QObject* parent = nullptr);

    /**
     * @brief Копирующий конструктор удалён.
     */
    Singltoneforclient(Singltoneforclient&) = delete;

    /**
     * @brief Оператор присваивания удалён.
     * @return Ссылка на текущий объект.
     */
    Singltoneforclient& operator=(Singltoneforclient&) = delete;

    friend class ClientDestroyer;

  public:
    /**
     * @brief Возвращает единственный экземпляр класса.
     * @return Указатель на единственный экземпляр класса.
     */
    static Singltoneforclient* getInstance();

    /**
     * @brief Отправляет сообщение на сервер.
     * @param msg Сообщение для отправки.
     */
    void sendMsgToServer(QString msg);

  signals:
    /**
     * @brief Сигнал, испускаемый при получении сообщения от сервера.
     * @param msg Сообщение от сервера.
     */
    void msgFromServer(QString msg);
};

#endif // SINGLTONEFORCLIENT_H
