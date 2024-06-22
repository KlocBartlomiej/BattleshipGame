#include "otherplayer.h"

OtherPlayer::OtherPlayer()
    : _isPlayerReady(false){}

std::optional<std::list<std::tuple<int,int>>> OtherPlayer::takeShot(int,int)
{
    return std::nullopt;
}

std::tuple<int,int> OtherPlayer::getShot()
{
    auto placeHolder = std::make_tuple(1,1);
    return placeHolder;
}

void OtherPlayer::hasMyLastShotHit(const bool hasMyLastShotHit)
{

}

void OtherPlayer::hasMyLastShotSunken(std::optional<std::list<std::tuple<int,int>>> neighboursOfSunkenShip)
{

}

void OtherPlayer::setPlayerReady(const bool isPlayerReady)
{
    if (socket->isOpen())
    {
        this->_isPlayerReady = isPlayerReady;
    }
}

bool OtherPlayer::isPlayerReady()
{
    return _isPlayerReady;
}

bool OtherPlayer::hasOpponentLost()
{
    auto placeHolder = false;
    return placeHolder;
}

void OtherPlayer::setSocket(QTcpSocket* socket)
{
    this->socket = socket;
}
