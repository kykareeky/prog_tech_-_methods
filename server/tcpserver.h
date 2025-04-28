/**
 * @file tcpserver.h
 * @brief Header of TcpServer class file
 */

// include guard
#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QTcpServer> 
#include <QTcpSocket>
#include <QList>

/**
 * @class TcpServer
 * @brief Class for TCP server operating.
 * 
 * TcpServer class is responsible for creating and operating a TCP server, 
 * processing client connections and transferring data.
 */
class TcpServer : public QObject
{
	Q_OBJECT // <- macros to enable meta-object features
public:
    /**
     * @brief Constructor for TcpServer.
     * @param parent pointer to parent object, default nullptr.
     */
    explicit TcpServer(QObject *parent = nullptr);

	/**
     * @brief  Destuctor for TcpServer.
     */
    ~TcpServer();

private slots:
    /**
     * @brief New connections slot.
     * 
     * This slot handles new client connections to the server.
     */
    void slotNewConnection();

    /**
     * @brief A slot for reading data from the client.
     * 
     * This slot is called when receiving data from a connected client.
     */
    void slotServerRead();

    /**
     * @brief Client disconnected slot.
     * 
     * This slot handles disconnecting the client from the server.
     */
    void slotClientDisconnected();

private:
    QTcpServer *mTcpServer; /**< Pointer to QTcpServer object for server operating. */
    QList<QTcpSocket*> mTcpSockets; /**< List of sockets for connected clients operating. */
};

#endif // TCPSERVER_H






