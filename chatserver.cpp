#include "chatserver.h"
#include "QtWebSockets/QWebSocketServer"
#include "QtWebSockets/QWebSocket"
#include <QtCore/QDebug>
#include <QNetworkAccessManager>
#include <QFile>
#include "downloader.h"

/**
 * @brief ChatServer::ChatServer
 * @param port
 * @param parent
 */
ChatServer::ChatServer(quint16 port, QObject *parent) :
    QObject(parent),
    m_pWebSocketServer(Q_NULLPTR),
    m_clients()
{
    m_pWebSocketServer = new QWebSocketServer(QStringLiteral("Chat Server"),
                                              QWebSocketServer::NonSecureMode,
                                              this);
    if (m_pWebSocketServer->listen(QHostAddress::Any, port))
    {
        qDebug() << "Chat Server listening on port" << port;
        connect(m_pWebSocketServer, SIGNAL(newConnection()),
                this, SLOT(onNewConnection()));
    }
}
/**
 * @brief ChatServer::~ChatServer
 */
ChatServer::~ChatServer()
{
    m_pWebSocketServer->close();
    qDeleteAll(m_clients.begin(), m_clients.end());
}

/**
 * @brief ChatServer::onNewConnection
 */
void ChatServer::onNewConnection()
{
    QWebSocket *pSocket = m_pWebSocketServer->nextPendingConnection();
    //connect(pSocket,SIGNAL(connected()),loader,SLOT());
    connect(pSocket, SIGNAL(textMessageReceived(QString)), this, SLOT(processMessage(QString)));
    connect(pSocket, SIGNAL(disconnected()), this, SLOT(socketDisconnected()));
    m_clients << pSocket;
    //QNetworkAccessManager;

//    std::fstream file("chatclient.html", std::ios::binary | std::ios::in);
//    QByteArray qwl;
//    unsigned char ch;
//    while (file.get(ch)) {
//              qwl += ch;
//         }
//    pSocket->sendBinaryMessage(qwl);
}

/**
 * @brief ChatServer::processMessage
 * @param message
 */
void ChatServer::processMessage(QString message)
{
    QWebSocket *pSender = qobject_cast<QWebSocket *>(sender());
    Q_FOREACH (QWebSocket *pClient, m_clients)
    {
        if (pClient != pSender)
        {
            pClient->sendTextMessage(message);
        }
    }
}

/**
 * @brief ChatServer::socketDisconnected
 */
void ChatServer::socketDisconnected()
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (pClient)
    {
        m_clients.removeAll(pClient);
        pClient->deleteLater();
    }
}
