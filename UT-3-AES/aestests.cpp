#include "aestests.h"

#define GENERATOR QRandomGenerator::global()->bounded(10000, 200000)

AESTests::AESTests()
{
    QByteArray key = "1234567890abcdef"; // 16-байтовый ключ AES-128
    aes = new AES(key.toStdString());
}

void AESTests::testRandomString()
{
    QString text = QString::number(GENERATOR);

    std::string encrypted = aes->encrypt(text.toStdString());
    std::string decrypted = aes->decrypt(encrypted);

    QCOMPARE(decrypted, text.toUtf8());
}

