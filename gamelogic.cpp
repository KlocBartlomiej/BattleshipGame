#include "gamelogic.h"
#include <QDebug>

GameLogic::GameLogic(const bool isGameStarted)
    : isGameStarted(isGameStarted)
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
    if(!isGameStarted || opponent == nullptr) { return; }
    opponent->takeShot(x,y);
}

void GameLogic::startPlaying()
{
    //TODO init some variables which will be used to determine end of the game
}
