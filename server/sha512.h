#ifndef SHA512_H
#define SHA512_H

#include <string>

// Объявление класса SHA512 для вычисления хэша SHA-512
class SHA512
{
  protected:
    typedef unsigned char uint8;            // 8-битное беззнаковое целое
    typedef unsigned int uint32;            // 32-битное беззнаковое целое
    typedef unsigned long long uint64;      // 64-битное беззнаковое целое

    // Константы для хэширования SHA-512
    const static uint64 sha512_k[];         // Константы для раундов
    static const unsigned int SHA384_512_BLOCK_SIZE = (1024 / 8); // Размер блока

  public:
    // Публичные методы класса
    void init();                            // Инициализация состояния хэша
    void update(const unsigned char *message, unsigned int len); // Обновление хэша данными
    void final(unsigned char *digest);      // Завершение хэширования и получение окончательного хэша

    // Размер хэша в байтах
    static const unsigned int DIGEST_SIZE = (512 / 8);

  protected:
    // Защищенные методы класса
    void transform(const unsigned char *message, unsigned int block_nb); // Преобразование сообщения в хэш
    unsigned int m_tot_len;                 // Общая длина сообщения
    unsigned int m_len;                     // Текущая длина сообщения
    unsigned char m_block[2 * SHA384_512_BLOCK_SIZE]; // Блок сообщения
    uint64 m_h[8];                          // Регистры хэша
};

// Функция для вычисления хэша SHA-512 для строки
std::string sha512(std::string input);

// Макросы для обработки битов и байтов
#define SHA2_SHFR(x, n)    (x >> n)
#define SHA2_ROTR(x, n)   ((x >> n) | (x << ((sizeof(x) << 3) - n)))
#define SHA2_ROTL(x, n)   ((x << n) | (x >> ((sizeof(x) << 3) - n)))
#define SHA2_CH(x, y, z)  ((x & y) ^ (~x & z))
#define SHA2_MAJ(x, y, z) ((x & y) ^ (x & z) ^ (y & z))
#define SHA512_F1(x) (SHA2_ROTR(x, 28) ^ SHA2_ROTR(x, 34) ^ SHA2_ROTR(x, 39))
#define SHA512_F2(x) (SHA2_ROTR(x, 14) ^ SHA2_ROTR(x, 18) ^ SHA2_ROTR(x, 41))
#define SHA512_F3(x) (SHA2_ROTR(x,  1) ^ SHA2_ROTR(x,  8) ^ SHA2_SHFR(x,  7))
#define SHA512_F4(x) (SHA2_ROTR(x, 19) ^ SHA2_ROTR(x, 61) ^ SHA2_SHFR(x,  6))
#define SHA2_UNPACK32(x, str)                     \
{                                                 \
        *((str) + 3) = (uint8) ((x)      );       \
        *((str) + 2) = (uint8) ((x) >>  8);       \
        *((str) + 1) = (uint8) ((x) >> 16);       \
        *((str) + 0) = (uint8) ((x) >> 24);       \
}
#define SHA2_UNPACK64(x, str)                     \
{                                                 \
        *((str) + 7) = (uint8) ((x)      );       \
        *((str) + 6) = (uint8) ((x) >>  8);       \
        *((str) + 5) = (uint8) ((x) >> 16);       \
        *((str) + 4) = (uint8) ((x) >> 24);       \
        *((str) + 3) = (uint8) ((x) >> 32);       \
        *((str) + 2) = (uint8) ((x) >> 40);       \
        *((str) + 1) = (uint8) ((x) >> 48);       \
        *((str) + 0) = (uint8) ((x) >> 56);       \
}
#define SHA2_PACK64(str, x)                       \
{                                                 \
        *(x) =   ((uint64) *((str) + 7)      )    \
               | ((uint64) *((str) + 6) <<  8)    \
               | ((uint64) *((str) + 5) << 16)    \
               | ((uint64) *((str) + 4) << 24)    \
               | ((uint64) *((str) + 3) << 32)    \
               | ((uint64) *((str) + 2) << 40)    \
               | ((uint64) *((str) + 1) << 48)    \
               | ((uint64) *((str) + 0) << 56);   \
}

#endif // SHA512_H
