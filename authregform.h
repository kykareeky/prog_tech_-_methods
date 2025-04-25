#ifndef AUTHREGFORM_H
#define AUTHREGFORM_H

#include <QWidget>

namespace Ui {
class AuthRegForm;
}

/**
 * @class AuthRegForm
 * @brief Класс формы авторизации и регистрации.
 *
 * Представляет собой окно для авторизации и регистрации пользователей.
 * Наследуется от QWidget и предоставляет интерфейс для работы с полями ввода,
 * кнопками и сигналами для отправки данных на сервер.
 */
class AuthRegForm : public QWidget
{
    Q_OBJECT

  public:
    /**
     * @brief Конструктор класса AuthRegForm.
     * @param parent Родительский виджет (по умолчанию nullptr).
     */
    explicit AuthRegForm(QWidget *parent = nullptr);

    /**
     * @brief Деструктор класса AuthRegForm.
     */
    ~AuthRegForm();

  private slots:
    /**
     * @brief Обработчик нажатия кнопки Auth (Авторизация).
     */
    void on_pushButtonAuth_clicked();

    /**
     * @brief Обработчик нажатия кнопки Reg (Регистрация).
     */
    void on_pushButtonReg_clicked();

    /**
     * @brief Обработчик нажатия кнопки (Изменить).
     */
    void on_pushButtonChange_clicked();

  private:
    Ui::AuthRegForm *ui; ///< Указатель на объект интерфейса формы.

  signals:
    /**
     * @brief Сигнал для отправки данных авторизации.
     * @param log Логин пользователя.
     * @param pass Пароль пользователя.
     */
    void auth(QString log, QString pass);

    /**
     * @brief Сигнал для отправки данных регистрации.
     * @param log Логин пользователя.
     * @param pass Пароль пользователя.
     * @param email Email пользователя.
     */
    void reg(QString log, QString pass, QString email);
};

#endif // AUTHREGFORM_H
