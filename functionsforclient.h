#ifndef FUNCTIONSFORCLIENT_H
#define FUNCTIONSFORCLIENT_H

#include <QObject>
#include "mainwindow.h"
#include "authregform.h"
#include "singltoneforclient.h"

/**
 * @class FunctionsForClient
 * @brief Класс, отвечающий за взаимодействие клиента с графическим интерфейсом и сервером.
 *
 * Класс FunctionsForClient предоставляет методы для аутентификации, регистрации и отправки задач
 * с использованием графического интерфейса. Также он обрабатывает сообщения от сервера.
 */
class FunctionsForClient: public QObject
{
    Q_OBJECT
  public:

    /**
     * @brief Конструктор класса FunctionsForClient.
     *
     * Инициализирует новый объект класса FunctionsForClient.
     */
    FunctionsForClient();

  signals:
    /**
     * @brief Сигнал успешной аутентификации.
     *
     * Этот сигнал посылается при успешной аутентификации пользователя.
     */
    void on_auth_ok();

    /**
     * @brief Сигнал с решением задачи.
     *
     * Этот сигнал посылается с текстом решения задачи.
     * @param text Текст решения задачи.
     */
    void solution(QString text);

  private:
    MainWindow * ui_main; ///< Указатель на объект главного окна приложения. */
    AuthRegForm * ui_auth; ///< Указатель на объект формы аутентификации и регистрации. */
    Singltoneforclient* client; ///< Указатель на объект класса Singltoneforclient, представляющий клиентское соединение. */
    QString login;

  public slots:
    /**
     * @brief Отправка данных для аутентификации.
     *
     * Метод для отправки логина и пароля для аутентификации на сервере.
     * @param log Логин пользователя.
     * @param pass Пароль пользователя.
     */
    void sendAuth(QString log, QString pass);

    /**
     * @brief Отправка данных для регистрации.
     *
     * Метод для отправки логина, пароля и электронной почты для регистрации на сервере.
     * @param log Логин пользователя.
     * @param pass Пароль пользователя.
     * @param email Электронная почта пользователя.
     */
    void sendReg(QString log, QString pass, QString email);

    /**
     * @brief Обработка сообщений от сервера.
     *
     * Метод для обработки сообщений, полученных от сервера.
     * @param msg Сообщение от сервера.
     */
    void msgHandler(QString msg);

    /**
     * @brief Отправка текста для выполнения задачи 1.
     *
     * Метод для отправки текста задачи 1 на сервер.
     * @param text plain text
     */
    void sendTask1(QString text);

    /**
     * @brief Отправка текста для выполнения задачи 2.
     *
     * Метод для отправки текста задачи 2 на сервер.
     * @param text plain text
     */
    void sendTask2(QString text);

    /**
     * @brief Отправка текста для выполнения задачи 3.
     *
     * Метод для отправки текста задачи 3 на сервер.
     * @param --- скопировать из хедера
     */
    void sendTask3(QString func, QString left, QString right, QString epsilon, QString maxIter);

    /**
     * @brief Отправка текста для выполнения задачи 4.
     *
     * Метод для отправки текста задачи 4 на сервер.
     * @param text plain text
     */
    void sendTask4(QString text);

    /**
     * @brief Отправка текста для запроса статы
     *
     * @param text plain text
     */
    void sendStat();
};

#endif // FUNCTIONSFORCLIENT_H
