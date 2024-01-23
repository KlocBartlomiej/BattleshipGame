#include "battlefieldcontroller.h"

BattlefieldController::BattlefieldController(QGridLayout * battlefield, QGridLayout * enemyBattlefield)
    :battlefield(battlefield),
        enemyBattlefield(enemyBattlefield),
        shipSetter(new ShipSetter())
{

}
//battlefield->addWidget(setShip(battlefield->itemAtPosition(i,j))i,j)
MyFrame * BattlefieldController::setNew(MyFrame* frame, bool isEnemyGround)
{
    if(isEnemyGround)
    {
        QObject::connect(frame, &MyFrame::clickedOn, shipSetter, &ShipSetter::enemyBattlefieldClickOn);
    }
    else
    {
        QObject::connect(frame, &MyFrame::clickedOn, shipSetter, &ShipSetter::battlefieldClickOn);
        QObject::connect(frame, &MyFrame::hoveredOn, shipSetter, &ShipSetter::battlefieldHoveredOn);
    }
    frame->setLineWidth(3);
    frame->setMidLineWidth(3);
    frame->setFrameStyle(QFrame::Panel | QFrame::Raised);
    return frame;
}

MyFrame * BattlefieldController::setEmpty(MyFrame* frame)
{
    frame->setFrameStyle(QFrame::Panel | QFrame::Raised);
    return frame;
}

MyFrame * BattlefieldController::setShip(MyFrame* frame)
{
    frame->setFrameStyle(QFrame::Box | QFrame::Raised);
    return frame;
}

MyFrame * BattlefieldController::setMiss(MyFrame* frame)
{
    frame->setFrameStyle(QFrame::Box | QFrame::Plain);
    return frame;
}

MyFrame * BattlefieldController::setHit(MyFrame* frame)
{
    frame->setFrameStyle(QFrame::Box | QFrame::Sunken);
    return frame;
}
