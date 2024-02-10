#ifndef BOT_H
#define BOT_H

#include "opponent.h"
#include "shipsetter.h"

#include <list>
#include <QRandomGenerator>
#include <algorithm>

using mastList = std::list<std::tuple<int,int>>;

class Bot : public Opponent
{
    bool isBotEnabled;

    QGridLayout* enemyBattlefield;
    ShipSetter* shipSetter;

    std::list<Ship> botsShips;
    mastList nextPossibleShots;
    mastList shotsWhichHit;
    mastList shotsFired;
    void populateNextShotsList(int,int);
    bool whichWayBotShouldAim(mastList);
public:
    Bot(QGridLayout*);

    bool hasOpponentLost();

    std::optional<mastList> takeShot(const int, const int);
    std::tuple<int,int> getShot();

    void hasMyLastShotHit(const bool);
    void hasMyLastShotSunken(std::optional<mastList>);

    void setPlayerReady(const bool);
    bool isplayerReady();
};

#endif // BOT_H
