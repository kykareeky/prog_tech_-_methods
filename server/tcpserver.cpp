#include "tcpserver.h"
#include "functionsforserver.h"
#include <QDebug>
#include <QCoreApplication>
#include <QString>

TcpServer::TcpServer(QObject *parent) : QObject(parent) 
{
    mTcpServer = new QTcpServer(this); // this for binding cur obj

	 /* signal-slot binding
                mTcpServer - signal src;
                &QTcpServer::newConnection - signal type;
                his - dst;
                MyTcpServer::slotNewConnection - slot (action)*/
    connect(mTcpServer, &QTcpServer::newConnection,
            this, &TcpServer::slotNewConnection);

    if (!mTcpServer->listen(QHostAddress::Any, 33333)) { // any IP to port 33333 listening
        qDebug() << "Server is not started"; // can't listnen
    } else {
        qDebug() << "Server is started"; // listneng
    }
}

TcpServer::~TcpServer()
{
    mTcpServer->close();
    qDeleteAll(mTcpSockets);
    mTcpSockets.clear();
}

void TcpServer::slotNewConnection()
{
	// QTcpSocket for a new client
    QTcpSocket *clientSocket = mTcpServer->nextPendingConnection(); 
    mTcpSockets << clientSocket; // add to connected clients list

	// ready read signal -> start reading slot 
    connect(clientSocket, &QTcpSocket::readyRead, this, &TcpServer::slotServerRead);

	// disconnected signal -> start disconected client slot 
    connect(clientSocket, &QTcpSocket::disconnected, this, &TcpServer::slotClientDisconnected);
    clientSocket->write("Hello Friend\r\n I am echo server\r\n");
}

void TcpServer::slotServerRead()
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender()); 
    if (!clientSocket)
        return;
    QString res = "";
    while (clientSocket->bytesAvailable() > 0) { // while reading bytes
        QByteArray array = clientSocket->readAll();
        res.append(array);
    }
    qDebug() << res.toUtf8();
    clientSocket->write(parsing(res));
}

void TcpServer::slotClientDisconnected() // obviously
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    if (!clientSocket)
        return;

    mTcpSockets.removeOne(clientSocket);
    clientSocket->deleteLater();
}


