#ifndef BOT_H
#define BOT_H

#include "opponent.h"
#include "shipsetter.h"

#include <list>
#include <QRandomGenerator>

class Bot : public Opponent
{
    bool isBotEnabled;

    QGridLayout* enemyBattlefield;
    ShipSetter* shipSetter;

    std::list<Ship> botsShips;
    std::list<std::tuple<int,int>> nextPossibleShots;
    std::list<std::tuple<int,int>> shotsFired;
public:
    Bot(QGridLayout*);

    bool hasOpponentLost();

    bool takeShot(const int, const int);
    std::tuple<int,int> getShot();

    void hasMyLastShotHit(const bool);
    void hasMyLastShotSunken(const bool);

    void setPlayerReady(const bool);
    bool isplayerReady();
};

#endif // BOT_H
