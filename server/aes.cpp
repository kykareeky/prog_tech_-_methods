#include "aes.h"
#include <openssl/evp.h>
#include <openssl/err.h>
#include <QByteArray>
#include <QDebug>

/**
 * @brief Конструктор AES-класса
 * @param key Ключ для шифрования (16 байт — AES-128)
 */
AES::AES(const std::string &key) : key_(key) {}

/**
 * @brief Шифрует текст с помощью AES-128 ECB и кодирует результат в Base64
 *
 * Использует OpenSSL EVP API для шифрования с padding.
 *
 * @param plaintext Открытый текст (std::string)
 * @return std::string Зашифрованный текст в формате Base64
 */
std::string AES::encrypt(const std::string &plaintext)
{
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    int outlen1, outlen2;

    // Буфер для зашифрованных данных
    QByteArray output(plaintext.size() + EVP_MAX_BLOCK_LENGTH, 0);

    // Инициализация AES-128 ECB
    EVP_EncryptInit_ex(ctx, EVP_aes_128_ecb(), nullptr,
                       reinterpret_cast<const unsigned char *>(key_.c_str()), nullptr);
    EVP_CIPHER_CTX_set_padding(ctx, 1);

    // Шифруем основной блок
    EVP_EncryptUpdate(ctx,
                      reinterpret_cast<unsigned char *>(output.data()), &outlen1,
                      reinterpret_cast<const unsigned char *>(plaintext.data()), plaintext.size());

    // Завершаем шифрование, дополняем padding
    EVP_EncryptFinal_ex(ctx,
                        reinterpret_cast<unsigned char *>(output.data()) + outlen1, &outlen2);

    EVP_CIPHER_CTX_free(ctx);

    // Результат -> Base64
    QByteArray final = output.left(outlen1 + outlen2);
    return final.toBase64().toStdString();
}

/**
 * @brief Расшифровывает Base64-строку, зашифрованную через AES-128 ECB
 *
 * Использует OpenSSL EVP API для дешифровки.
 *
 * @param base64_ciphertext Шифртекст в формате Base64
 * @return std::string Расшифрованный открытый текст
 */
std::string AES::decrypt(const std::string &base64_ciphertext)
{
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    int outlen1, outlen2;

    // Декодируем Base64 -> raw
    QByteArray encrypted = QByteArray::fromBase64(QByteArray::fromStdString(base64_ciphertext));
    QByteArray output(encrypted.size(), 0);

    // Инициализация AES-128 ECB
    EVP_DecryptInit_ex(ctx, EVP_aes_128_ecb(), nullptr,
                       reinterpret_cast<const unsigned char *>(key_.c_str()), nullptr);
    EVP_CIPHER_CTX_set_padding(ctx, 1);

    // Расшифровка
    EVP_DecryptUpdate(ctx,
                      reinterpret_cast<unsigned char *>(output.data()), &outlen1,
                      reinterpret_cast<const unsigned char *>(encrypted.data()), encrypted.size());

    // Завершение (учёт padding)
    EVP_DecryptFinal_ex(ctx,
                        reinterpret_cast<unsigned char *>(output.data()) + outlen1, &outlen2);

    EVP_CIPHER_CTX_free(ctx);

    QByteArray final = output.left(outlen1 + outlen2);
    return final.toStdString();
}
