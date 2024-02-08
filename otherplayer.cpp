#include "otherplayer.h"

OtherPlayer::OtherPlayer()
    : isPlayerReady(false){}

bool OtherPlayer::takeShot(int,int)
{
    auto placeHolder = false;
    return placeHolder;
}

std::tuple<int,int> OtherPlayer::getShot()
{
    auto placeHolder = std::make_tuple(1,1);
    return placeHolder;
}

void OtherPlayer::hasMyLastShotHit(const bool hasMyLastShotHit)
{

}

void OtherPlayer::hasMyLastShotSunken(const bool hasMyLastShotSunken)
{

}

void OtherPlayer::setPlayerReady(const bool isBotEnabled)
{
    this->isPlayerReady = isBotEnabled;
}

bool OtherPlayer::isplayerReady()
{
    return isPlayerReady;
}

bool OtherPlayer::hasOpponentLost()
{
    auto placeHolder = false;
    return placeHolder;
}
