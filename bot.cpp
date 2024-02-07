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

    while(myShips.size() != classicGameShipsNumber)
    {
        x = QRandomGenerator::global()->bounded(1, 10) + 1;
        y = QRandomGenerator::global()->bounded(1, 10) + 1;

        if((x+y)%2)
        {
            shipSetter->changeDrawingDirection();
        }
        qDebug() << x << " " << y;

        QMetaObject::invokeMethod(shipSetter,"battlefieldHoveredOn",Q_ARG(int,x),Q_ARG(int,y));
        QMetaObject::invokeMethod(shipSetter,"battlefieldClickOn",Q_ARG(int,x),Q_ARG(int,y));

        myShips = shipSetter->getShips();
        qDebug() << "ship count " << myShips.size();
    }
}

bool Bot::takeShot(const int x, const int y)
{
    qDebug() << "I'm bot";
    if(MyFrame::isShip(x,y,enemyBattlefield))
    {
        //TODO make sure this mast was removed from myShips list, or GameLogic should delete it and keep track of sunken ships
        MyFrame::setHit(x,y,enemyBattlefield);
        return true;
    }
    if(!MyFrame::isHit(x,y,enemyBattlefield))
    {
        MyFrame::setMiss(x,y,enemyBattlefield);
    }
    return false;
}

std::tuple<int,int> Bot::getShot()
{
    if(nextPossibleShots.empty())
    {
        while(true)
        {
            std::tuple<int,int> shipMast = std::make_tuple(
                QRandomGenerator::global()->bounded(1, 10) + 1,
                QRandomGenerator::global()->bounded(1, 10) + 1);
            auto it = std::find(shotsFired.begin(), shotsFired.end(), shipMast);
            if(it == shotsFired.end())
            {
                shotsFired.push_back(shipMast);
                return shipMast;
            }
        }
    }
    auto nextShot = nextPossibleShots.front();
    nextPossibleShots.pop_front();
    return nextShot;
}

void Bot::isMyLastShotHit(const bool isMyLastShotHit)
{

}

void Bot::isMyLastShotSunken(const bool isMyLastShotSunken)
{

}

void Bot::setPlayerReady(const bool isBotEnabled)
{
    this->isBotEnabled = isBotEnabled;
}

bool Bot::isplayerReady()
{
    return isBotEnabled;
}
