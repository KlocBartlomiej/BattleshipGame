#ifndef OTHERPLAYER_H
#define OTHERPLAYER_H

#include "opponent.h"

#include <tuple>

class otherPlayer : public Opponent
{
    bool isPlayerReady;
public:
    otherPlayer();
    bool takeShot(int,int);
    std::tuple<int,int> getShot();
    void isMyLastShotHit(const bool);
    void isMyLastShotSunken(const bool);
    void setPlayerReady(const bool);
    bool isplayerReady();
};

#endif // OTHERPLAYER_H
