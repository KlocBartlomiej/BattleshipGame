#ifndef BOT_H
#define BOT_H

#include "opponent.h"

#include <list>
#include <QRandomGenerator>

class Bot : public Opponent
{
    std::list<std::tuple<int,int>> nextPossibleShots;
    std::list<std::tuple<int,int>> shotsFired;
public:
    Bot();
    void takeShot(int,int);
    std::tuple<int,int> getShot();
};

#endif // BOT_H
