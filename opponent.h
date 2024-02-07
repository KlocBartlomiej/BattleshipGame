#ifndef OPPONENT_H
#define OPPONENT_H

#include<tuple>

class Opponent
{
public:
    virtual bool takeShot(int,int) = 0;
    virtual std::tuple<int,int> getShot() = 0;
    virtual void isMyLastShotHit(const bool) = 0;
    virtual void isMyLastShotSunken(const bool) = 0;
    virtual void setPlayerReady(const bool) = 0;
    virtual bool isplayerReady() = 0;
};

#endif // OPPONENT_H
