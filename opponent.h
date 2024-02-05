#ifndef OPPONENT_H
#define OPPONENT_H

#include<tuple>

class Opponent
{
public:
    virtual void takeShot(int,int) = 0;
    virtual std::tuple<int,int> getShot() = 0;
};

#endif // OPPONENT_H
