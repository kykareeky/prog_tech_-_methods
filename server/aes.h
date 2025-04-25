/**
 * @file AES.h
 * @brief Определение класса для реализации алгоритма шифрования AES
 */

#ifndef AES_H
#define AES_H

#include <string>
#include <vector>

/**
 * @class AES
 * @brief Класс для реализации алгоритма шифрования AES.
 */
class AES
{
  public:
    /**
     * @brief Конструктор класса AES.
     * @param key Ключ шифрования в виде строки.
     */
    AES(const std::string &key);

    /**
     * @brief Метод для шифрования текста.
     * @param plainText Открытый текст, который нужно зашифровать.
     * @return Зашифрованный текст в виде строки.
     */
    std::string encrypt(const std::string &plainText);

    /**
     * @brief Метод для расшифровки текста.
     * @param cipherText Зашифрованный текст, который нужно расшифровать.
     * @return Расшифрованный текст в виде строки.
     */
    std::string decrypt(const std::string &cipherText);

  private:
    /**
     * @brief Генерация расписания ключей.
     * @param key Ключ шифрования в виде вектора байтов.
     * @return Вектор векторов байтов, представляющих расписание ключей.
     */
    std::vector<std::vector<unsigned char>> keySchedule(const std::vector<unsigned char> &key);

    /**
     * @brief Добавление раундового ключа к состоянию.
     * @param state Текущее состояние в виде вектора байтов.
     * @param roundKey Раундовый ключ в виде вектора байтов.
     * @return Новое состояние после добавления раундового ключа.
     */
    std::vector<unsigned char> addRoundKey(const std::vector<unsigned char> &state, const std::vector<unsigned char> &roundKey);

    /**
     * @brief Замена байтов в состоянии согласно S-блоку.
     * @param state Текущее состояние в виде вектора байтов.
     * @return Новое состояние после замены байтов.
     */
    std::vector<unsigned char> subBytes(const std::vector<unsigned char> &state);

    /**
     * @brief Обратная замена байтов в состоянии согласно S-блоку.
     * @param state Текущее состояние в виде вектора байтов.
     * @return Новое состояние после обратной замены байтов.
     */
    std::vector<unsigned char> invSubBytes(const std::vector<unsigned char> &state);

    /**
     * @brief Циклический сдвиг строк состояния.
     * @param state Текущее состояние в виде вектора байтов.
     * @return Новое состояние после сдвига строк.
     */
    std::vector<unsigned char> shiftRows(const std::vector<unsigned char> &state);

    /**
     * @brief Обратный циклический сдвиг строк состояния.
     * @param state Текущее состояние в виде вектора байтов.
     * @return Новое состояние после обратного сдвига строк.
     */
    std::vector<unsigned char> invShiftRows(const std::vector<unsigned char> &state);

    /**
     * @brief Преобразование столбцов состояния.
     * @param state Текущее состояние в виде вектора байтов.
     * @return Новое состояние после преобразования столбцов.
     */
    std::vector<unsigned char> mixColumns(const std::vector<unsigned char> &state);

    /**
     * @brief Обратное преобразование столбцов состояния.
     * @param state Текущее состояние в виде вектора байтов.
     * @return Новое состояние после обратного преобразования столбцов.
     */
    std::vector<unsigned char> invMixColumns(const std::vector<unsigned char> &state);

    /**
     * @brief Дополнение открытого текста до нужного размера.
     * @param plainText Открытый текст в виде строки.
     * @return Дополненный текст в виде строки.
     */
    std::string pad(const std::string &plainText);

    /**
     * @brief Удаление дополнения из текста.
     * @param plainText Текст с дополнением в виде строки.
     * @return Текст без дополнения в виде строки.
     */
    std::string unpad(const std::string &plainText);

    /**
     * @brief Преобразование байтов в шестнадцатеричное представление.
     * @param bytes Вектор байтов.
     * @return Строка в шестнадцатеричном формате.
     */
    std::string bytesToHex(const std::vector<unsigned char> &bytes);

    /**
     * @brief Преобразование шестнадцатеричной строки в вектор байтов.
     * @param hex Строка в шестнадцатеричном формате.
     * @return Вектор байтов.
     */
    std::vector<unsigned char> hexToBytes(const std::string &hex);

    std::vector<unsigned char> m_key; ///< Ключ шифрования.
    std::vector<std::vector<unsigned char>> m_roundKeys; ///< Раундовые ключи.
};

#endif
