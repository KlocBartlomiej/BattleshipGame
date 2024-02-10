#include "bot.h"
#include<QDebug>

Bot::Bot(QGridLayout* enemyBattlefield)
    : enemyBattlefield(enemyBattlefield)
    , isBotEnabled(false)
    , shipSetter(new ShipSetter(enemyBattlefield,false))
{
    shipSetter->setAllShips();
    int x,y;
    int classicGameShipsNumber = 10;

    while(botsShips.size() != classicGameShipsNumber)
    {
        x = QRandomGenerator::global()->bounded(0, 10) + 1;
        y = QRandomGenerator::global()->bounded(0, 10) + 1;

        if((x+y)%2)
        {
            shipSetter->changeDrawingDirection();
        }

        QMetaObject::invokeMethod(shipSetter,"battlefieldHoveredOn",Q_ARG(int,x),Q_ARG(int,y));
        QMetaObject::invokeMethod(shipSetter,"battlefieldClickOn",Q_ARG(int,x),Q_ARG(int,y));

        botsShips = shipSetter->getShips();
    }
}

std::optional<std::list<std::tuple<int,int>>> Bot::takeShot(const int x, const int y)
{
    std::optional<std::list<std::tuple<int,int>>> neighboursOfSunkenShip = std::nullopt;
    if(MyFrame::isShip(x,y,enemyBattlefield))
    {
        auto ship = std::begin(botsShips);
        while(ship != std::end(botsShips))
        {
            if(ship->searchAndRemove(std::make_tuple(x,y)))
            {
                if(ship->isShipSunken())
                {
                    neighboursOfSunkenShip.emplace(ship->getNeighbours());
                    botsShips.erase(ship);
                }
                break;
            }
            else
            {
                ship++;
            }
        }
        MyFrame::setHit(x,y,enemyBattlefield);
    }
    if(!MyFrame::isHit(x,y,enemyBattlefield))
    {
        MyFrame::setMiss(x,y,enemyBattlefield);
    }
    return neighboursOfSunkenShip;
}

std::tuple<int,int> Bot::getShot()
{
    if(nextPossibleShots.empty())
    {
        while(true)
        {
            std::tuple<int,int> shipMast = std::make_tuple(
                QRandomGenerator::global()->bounded(0, 10) + 1,
                QRandomGenerator::global()->bounded(0, 10) + 1);
            auto it = std::find(shotsFired.begin(), shotsFired.end(), shipMast);
            if(it == shotsFired.end())
            {
                shotsFired.push_back(shipMast);
                qDebug() << "next bot's shot: " << std::get<0>(shipMast) << " " << std::get<1>(shipMast);
                return shipMast;
            }
        }
    }
    auto nextShot = nextPossibleShots.front();
    nextPossibleShots.pop_front();
    return nextShot;
}

void Bot::hasMyLastShotHit(const bool hasMyLastShotHit)
{
    if(hasMyLastShotHit)
    {
        //TODO when ships can't be touching ready, then I can predict which direction bot should shoot next to sunk the ship
    }
}

void Bot::hasMyLastShotSunken(std::optional<std::list<std::tuple<int,int>>> neighboursOfSunkenShip)
{
    if(neighboursOfSunkenShip)
    {
        for(auto neighbour : *neighboursOfSunkenShip)
        {
            shotsFired.push_back(neighbour);
        }
        nextPossibleShots.clear();
    }
}

void Bot::setPlayerReady(const bool isBotEnabled)
{
    this->isBotEnabled = isBotEnabled;
}

bool Bot::isplayerReady()
{
    return isBotEnabled;
}

bool Bot::hasOpponentLost()
{
    return botsShips.size() == 0;
}
