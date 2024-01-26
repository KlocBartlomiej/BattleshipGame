#include "battlefieldcontroller.h"
#include <QDebug>

BattlefieldController::BattlefieldController(QGridLayout * battlefield, QGridLayout * enemyBattlefield)
    :battlefield(battlefield)
    , enemyBattlefield(enemyBattlefield)
    , shipSetter(new ShipSetter(battlefield))
    , isGameStarted(false){}

MyFrame* BattlefieldController::setNew(MyFrame* frame,bool isEnemyGround)
{
    if(isEnemyGround)
    {
        //TODO: new object for playing, setter will only take care of our battlefield
        //slot for enemy battlefield can be held by bot or socket class
        //QObject::connect(frame, &MyFrame::clickedOn, , &::enemyBattlefieldClickOn);
    }
    else
    {
        QObject::connect(frame, &MyFrame::clickedOn, shipSetter, &ShipSetter::battlefieldClickOn);
        QObject::connect(frame, &MyFrame::hoveredOn, shipSetter, &ShipSetter::battlefieldHoveredOn);
    }
    frame->setNew();
    return frame;
}
