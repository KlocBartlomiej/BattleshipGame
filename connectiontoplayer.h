#ifndef CONNECTIONTOPLAYER_H
#define CONNECTIONTOPLAYER_H

#include <QObject>
#include <QTextEdit>
#include <QMetaEnum>
#include <QTcpServer>
#include <QTcpSocket>

class ConnectionToPlayer : public QObject
{
    Q_OBJECT
    QTcpServer* server;
    QTcpSocket* socket;
    QTextEdit* textEdit;

    const int MAX_PENDING_CONNECTIONS = 1;

    void acceptConnection();

public:
    ConnectionToPlayer(QTextEdit*);
    std::tuple<QString,int> startListening();
    void connectToPlayer(const QString ip, const int port);

    void SocketConnected();
    void SocketDisconnected();
    void SocketStateChanged(QAbstractSocket::SocketState);
    void SocketErrorOccurred(QAbstractSocket::SocketError);

signals:
    void playerConnected(QTcpSocket*);
};

#endif // CONNECTIONTOPLAYER_H
