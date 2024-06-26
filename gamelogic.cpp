#include "gamelogic.h"
#include <QDebug>

GameLogic::GameLogic(QGridLayout* battlefield,QGridLayout* enemyBattlefield, const bool isGameStarted)
    : playerBattlefield(battlefield)
    , enemyBattlefield(enemyBattlefield)
    , isGameStarted(isGameStarted)
    , opponent(nullptr){}

void GameLogic::setOpponentInstance(Opponent* opponent)
{
    this->opponent = opponent;
}

void GameLogic::gameFinished(const QString msg)
{
    isGameStarted = false;
    emit gameEnded(msg);
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
    if(!isGameStarted) { return; }
    if(opponent == nullptr) { return; }
    if(!opponent->isPlayerReady()) { return; }
    if(std::find(shotsFired.begin(),shotsFired.end(),std::make_tuple(x,y)) != shotsFired.end())
    {
        return;
    }
    else
    {
        shotsFired.push_back(std::make_tuple(x,y));
    }

    opponent->setPlayerReady(false);
    if(auto neighbours = opponent->takeShot(x,y))
    {
        for(auto neighbour : *neighbours)
        {
            shotsFired.push_back(neighbour);
            MyFrame::setMiss(std::get<0>(neighbour),std::get<1>(neighbour),enemyBattlefield);
        }
        enemysSunkenShips++;
    }

    std::optional<mastList> neighboursOfSunkenShip = std::nullopt;

    std::tuple<int,int> enemyShot = opponent->getShot();
    bool isOpponentsLastShotHit = false, isOpponentsLastShotSunken = false;
    auto ship = std::begin(ships);
    while(ship != std::end(ships))
    {
        if(ship->searchAndRemove(enemyShot))
        {
            isOpponentsLastShotHit = true;
            MyFrame::setHit(std::get<0>(enemyShot),std::get<1>(enemyShot),playerBattlefield);
            if(ship->isShipSunken())
            {
                isOpponentsLastShotSunken = true;
                neighboursOfSunkenShip.emplace(ship->getNeighbours());
                playersSunkenShips++;
                ships.erase(ship);
            }
            break;
        }
        ship++;
    }

    if(!isOpponentsLastShotHit)
    {
        MyFrame::setMiss(std::get<0>(enemyShot),std::get<1>(enemyShot),playerBattlefield);
    }

    opponent->hasMyLastShotHit(isOpponentsLastShotHit);
    opponent->hasMyLastShotSunken(isOpponentsLastShotSunken ? neighboursOfSunkenShip : std::nullopt);

    if(isOpponentsLastShotSunken)
    {
        for(auto neighbour : *neighboursOfSunkenShip)
        {
            MyFrame::setMiss(std::get<0>(neighbour),std::get<1>(neighbour),playerBattlefield);
        }
    }

    int classicGameNumberOfShips = 10;
    if(opponent->hasOpponentLost())
    {
        return gameFinished("Congratulations :D");
    }

    if(playersSunkenShips == classicGameNumberOfShips)
    {
        return gameFinished("You've been defeated");
    }

    opponent->setPlayerReady(true);
}

void GameLogic::startPlaying()
{
    shotsFired.clear();
    gameStarted();
    playersSunkenShips = 0;
    enemysSunkenShips = 0;
}

void GameLogic::playerShipsAreReady(std::list<Ship> ships)
{
    this->ships = ships;
    opponent->setPlayerReady(true);
}

void GameLogic::newPlayerConnected(QTcpSocket* socket)
{
    OtherPlayer* otherPlayer = new OtherPlayer();
    otherPlayer->setSocket(socket);
    otherPlayer->setPlayerReady(true);
}

