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

std::optional<mastList> Bot::takeShot(const int x, const int y)
{
    std::optional<mastList> neighboursOfSunkenShip = std::nullopt;
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
    shotsFired.push_back(nextShot);
    nextPossibleShots.pop_front();
    return nextShot;
}

void Bot::hasMyLastShotHit(const bool hasMyLastShotHit)
{
    if(hasMyLastShotHit)
    {
        auto lastShot = shotsFired.back();
        int x = std::get<0>(lastShot);
        int y = std::get<1>(lastShot);
        shotsWhichHit.push_back(std::make_tuple(x,y));
        nextPossibleShots.clear();
        populateNextShotsList(x,y);
        qDebug() << "list after populate: " << nextPossibleShots.size();
    }
}

void Bot::populateNextShotsList(int x, int y)
{
    mastList nextShots;
    if(whichWayBotShouldAim({std::make_tuple(x-1,y),std::make_tuple(x+1,y)}))
    {
        int _x = x;
        for(;_x >= 1;_x--)
        {
            if(std::find(shotsWhichHit.begin(),shotsWhichHit.end(),std::make_tuple(_x,y)) != shotsWhichHit.end()) { continue; }
            if(std::find(shotsFired.begin(),shotsFired.end(),std::make_tuple(_x,y)) != shotsFired.end()) { break; }
            nextPossibleShots.push_back(std::make_tuple(_x,y));
            break;
        }
        _x = x;
        for(;_x <= 10;_x++)
        {
            if(std::find(shotsWhichHit.begin(),shotsWhichHit.end(),std::make_tuple(_x,y)) != shotsWhichHit.end()) { continue; }
            if(std::find(shotsFired.begin(),shotsFired.end(),std::make_tuple(_x,y)) != shotsFired.end()) { break; }
            nextPossibleShots.push_back(std::make_tuple(_x,y));
            break;
        }
    }
    else if(whichWayBotShouldAim({std::make_tuple(x,y-1),std::make_tuple(x,y+1)}))
    {
        int _y = y;
        for(;_y >= 1;_y--)
        {
            if(std::find(shotsWhichHit.begin(),shotsWhichHit.end(),std::make_tuple(x,_y)) != shotsWhichHit.end()) { continue; }
            if(std::find(shotsFired.begin(),shotsFired.end(),std::make_tuple(x,_y)) != shotsFired.end()) { break; }
            nextPossibleShots.push_back(std::make_tuple(x,_y));
            break;
        }
        _y = y;
        for(;_y <= 10;_y++)
        {
            if(std::find(shotsWhichHit.begin(),shotsWhichHit.end(),std::make_tuple(x,_y)) != shotsWhichHit.end()) { continue; }
            if(std::find(shotsFired.begin(),shotsFired.end(),std::make_tuple(x,_y)) != shotsFired.end()) { break; }
            nextPossibleShots.push_back(std::make_tuple(x,_y));
            break;
        }
    }
    else
    {
        nextPossibleShots.push_back(std::make_tuple(x-1,y));
        nextPossibleShots.push_back(std::make_tuple(x,y-1));
        nextPossibleShots.push_back(std::make_tuple(x+1,y));
        nextPossibleShots.push_back(std::make_tuple(x,y+1));
        nextPossibleShots.remove_if([](std::tuple<int,int> mast){
            int x = std::get<0>(mast);
            int y = std::get<1>(mast);
            return (x > 10 || x < 1 || y > 10 || y < 1);
        });
    }
}

bool Bot::whichWayBotShouldAim(mastList list)
{
    list.remove_if([](std::tuple<int,int> mast){
        int x = std::get<0>(mast);
        int y = std::get<1>(mast);
        return (x > 10 || x < 1 || y > 10 || y < 1);
    });
    for(auto mast : list)
    {
        int x = std::get<0>(mast);
        int y = std::get<1>(mast);
        if(std::find(shotsWhichHit.begin(),shotsWhichHit.end(),std::make_tuple(x,y)) != shotsWhichHit.end())
        {
            return true;
        }
    }
    return false;
}

void Bot::hasMyLastShotSunken(std::optional<mastList> neighboursOfSunkenShip)
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
