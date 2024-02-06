#include "battlefieldcontroller.h"
#include <QDebug>

BattlefieldController::BattlefieldController(QGridLayout * battlefield, QGridLayout * enemyBattlefield, const bool isGameStarted)
    :battlefield(battlefield)
    , enemyBattlefield(enemyBattlefield)
    , shipSetter(new ShipSetter(battlefield,true))
    , gameInstance(new GameLogic(battlefield,isGameStarted)){}

MyFrame* BattlefieldController::setNew(MyFrame* frame,bool isEnemyGround)
{
    if(isEnemyGround)
    {
        QObject::connect(frame, &MyFrame::clickedOn, gameInstance, &GameLogic::enemyBattlefieldClickOn);
    }
    else
    {
        QObject::connect(frame, &MyFrame::clickedOn, shipSetter, &ShipSetter::battlefieldClickOn);
        QObject::connect(frame, &MyFrame::hoveredOn, shipSetter, &ShipSetter::battlefieldHoveredOn);
    }
    frame->setNew();
    return frame;
}
