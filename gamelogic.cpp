#include "gamelogic.h"
#include <QDebug>

GameLogic::GameLogic(QGridLayout * battlefield, const bool isGameStarted)
    : playerBattlefield(battlefield)
    , isGameStarted(isGameStarted)
    , opponent(nullptr){}

void GameLogic::setOpponentInstance(Opponent* opponent)
{
    this->opponent = opponent;
}

void GameLogic::gameStarted()
{
    isGameStarted = true;
}

bool GameLogic::hasGameStarted()
{
    return isGameStarted;
}

void GameLogic::enemyBattlefieldClickOn(const int x, const int y)
{
    qDebug() << "clicked " << x << " " << y;
    if(!isGameStarted) { return; }
    if(opponent == nullptr) { return; }
    if(!opponent->isplayerReady()) { return; }

    opponent->setPlayerReady(false);
    opponent->takeShot(x,y);

    std::tuple<int,int> enemyShot = opponent->getShot();
    bool isHit = false, isSunken = false;
    for(auto ship : ships)
    {
        if(ship.searchAndRemove(enemyShot))
        {
            isHit = true;
            if(ship.isShipSunken())
            {
                isSunken = true;
                //TODO remove ship from ships list, at this point app should check if somebody won already
            }
        }
    }
    opponent->isMyLastShotHit(isHit);
    opponent->isMyLastShotSunken(isSunken);
    opponent->setPlayerReady(true);
}

void GameLogic::startPlaying()
{
    //TODO init some variables which will be used to determine end of the game
}

void GameLogic::playerShipsAreReady()
{
    opponent->setPlayerReady(true);
}
