#ifndef AES_H
#define AES_H

#include <QString>
#include <QByteArray>
#include <string>

/**
 * @brief AES шифрование/дешифрование в режиме ECB + Base64
 */
class AES
{
  public:
    /**
     * @brief Конструктор AES
     * @param key Строка ключа (16 байт для AES-128)
     */
    AES(const std::string &key);

    /**
     * @brief Зашифровать строку и вернуть в формате Base64
     * @param plaintext Открытый текст
     * @return Зашифрованный Base64-текст
     */
    std::string encrypt(const std::string &plaintext);

    /**
     * @brief Расшифровать Base64-строку
     * @param base64_ciphertext Зашифрованный Base64-текст
     * @return Расшифрованный текст
     */
    std::string decrypt(const std::string &base64_ciphertext);

  private:
    std::string key_;
};

#endif // AES_H
