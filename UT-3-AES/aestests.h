#ifndef AESTESTS_H
#define AESTESTS_H

#include <QTest>
#include <QRandomGenerator>
#include <QJsonDocument>
#include <QJsonObject>
#include "../echoServer/aes.h"  // Указываем правильный относительный путь

class AESTests : public QObject
{
    Q_OBJECT
  private:
    AES* aes;
  public:
    AESTests();

  private slots:
    void testRandomString();
};

#endif // AESTESTS_H

