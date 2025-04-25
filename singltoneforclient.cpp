#include "singltoneforclient.h"

Singltoneforclient* Singltoneforclient::p_instance = nullptr;
SingltoneforclientDestroyer Singltoneforclient::destroyer;

Singltoneforclient::Singltoneforclient(QObject* parent) : QObject(parent)
{
    mTcpSocket = new QTcpSocket(this);
    mTcpSocket->connectToHost("127.0.0.1", 33333);

    connect(mTcpSocket, SIGNAL(readyRead()), this, SLOT(slotServerRead()));
}

Singltoneforclient* Singltoneforclient::getInstance()
{
    if (!p_instance)
    {
        p_instance = new Singltoneforclient();
        destroyer.initialize(p_instance);
    }
    return p_instance;
}
void Singltoneforclient::sendMsgToServer(QString msg)
{
    mTcpSocket->write(msg.toUtf8());
}

void Singltoneforclient::slotServerRead()
{
    QString msg = "";

    while (mTcpSocket->bytesAvailable() > 0)
    {
        QByteArray array = mTcpSocket->readAll();
        msg.append(array);
    }

    qDebug() << msg;
    emit msgFromServer(msg);
}
