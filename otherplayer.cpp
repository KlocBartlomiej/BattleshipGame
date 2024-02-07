#include "otherplayer.h"

otherPlayer::otherPlayer()
    : isPlayerReady(false){}

bool otherPlayer::takeShot(int,int)
{
    return false;
}

std::tuple<int,int> otherPlayer::getShot()
{
    return std::make_tuple(1,1);
}

void otherPlayer::isMyLastShotHit(const bool)
{

}

void otherPlayer::isMyLastShotSunken(const bool)
{

}

void otherPlayer::setPlayerReady(const bool isBotEnabled)
{
    this->isPlayerReady = isBotEnabled;
}

bool otherPlayer::isplayerReady()
{
    return isPlayerReady;
}
