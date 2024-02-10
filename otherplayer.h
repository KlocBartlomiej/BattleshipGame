#ifndef OTHERPLAYER_H
#define OTHERPLAYER_H

#include "opponent.h"

#include <tuple>

class OtherPlayer : public Opponent
{
    bool isPlayerReady;
public:
    OtherPlayer();

    bool hasOpponentLost();

    std::optional<std::list<std::tuple<int,int>>> takeShot(int,int);
    std::tuple<int,int> getShot();

    void hasMyLastShotHit(const bool);
    void hasMyLastShotSunken(std::optional<std::list<std::tuple<int,int>>>);

    void setPlayerReady(const bool);
    bool isplayerReady();
};

#endif // OTHERPLAYER_H
