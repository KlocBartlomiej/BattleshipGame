#ifndef OTHERPLAYER_H
#define OTHERPLAYER_H

#include "opponent.h"

#include <tuple>

class otherPlayer : public Opponent
{
public:
    otherPlayer();
    bool takeShot(int,int);
    std::tuple<int,int> getShot();
    void isMyLastShotHit(const bool);
    void isMyLastShotSunken(const bool);
};

#endif // OTHERPLAYER_H
