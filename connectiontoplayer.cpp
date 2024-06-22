#include "connectiontoplayer.h"

ConnectionToPlayer::ConnectionToPlayer(QTextEdit* textEdit)
    : server(new QTcpServer())
    , socket(new QTcpSocket())
    , textEdit(textEdit)
{
    //socket signals
    QObject::connect(socket, &QTcpSocket::connected, this, &ConnectionToPlayer::SocketConnected);
    QObject::connect(socket, &QTcpSocket::disconnected, this, &ConnectionToPlayer::SocketDisconnected);
    QObject::connect(socket, &QTcpSocket::stateChanged, this, &ConnectionToPlayer::SocketStateChanged);
    QObject::connect(socket, &QTcpSocket::errorOccurred, this, &ConnectionToPlayer::SocketErrorOccurred);

    //server signals
    QObject::connect(server, &QTcpServer::newConnection, this, &ConnectionToPlayer::acceptConnection);
}

void ConnectionToPlayer::SocketConnected()
{
    textEdit->append("Other Player connected.");
}

void ConnectionToPlayer::SocketDisconnected()
{
    textEdit->append("Other Player disconnected.");
}

void ConnectionToPlayer::SocketStateChanged(QAbstractSocket::SocketState state)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<QAbstractSocket::SocketState>();
    textEdit->append(metaEnum.valueToKey(state));
}

void ConnectionToPlayer::SocketErrorOccurred(QAbstractSocket::SocketError error)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<QAbstractSocket::SocketError>();
    textEdit->append(metaEnum.valueToKey(error));
}

void ConnectionToPlayer::acceptConnection()
{
    emit playerConnected(server->nextPendingConnection());
}

std::tuple<QString,int> ConnectionToPlayer::startListening()
{
    server->listen();
    return std::make_tuple(server->serverAddress().toString(),server->serverPort());
}

void ConnectionToPlayer::connectToPlayer(const QString ip, const int port)
{
    QHostAddress hostAddress(ip);
    if(QAbstractSocket::IPv4Protocol == hostAddress.protocol())
    {
        socket->connectToHost(ip, port);
        emit playerConnected(socket);
    } else {
        textEdit->append("IP address which you provided is incorrect.");
    }
}
