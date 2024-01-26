#include "battlefieldcontroller.h"
#include <QDebug>

BattlefieldController::BattlefieldController(QGridLayout * battlefield, QGridLayout * enemyBattlefield)
    :battlefield(battlefield)
    , enemyBattlefield(enemyBattlefield)
    , shipSetter(new ShipSetter(battlefield))
    , isGameStarted(false){}

MyFrame* BattlefieldController::setNew(MyFrame* frame, bool isEnemyGround)
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
    frame->setLineWidth(3);
    frame->setMidLineWidth(3);
    frame->setFrameStyle(QFrame::Panel | QFrame::Raised);
    return frame;
}

MyFrame* BattlefieldController::setEmpty(MyFrame* frame)
{
    frame->setFrameStyle(QFrame::Panel | QFrame::Raised);
    return frame;
}

MyFrame* BattlefieldController::setShip(MyFrame* frame)
{
    frame->setFrameStyle(QFrame::Box | QFrame::Raised);
    return frame;
}

bool BattlefieldController::isShip(int x, int y)
{
    MyFrame* frame = qobject_cast<MyFrame*>(battlefield->itemAtPosition(x,y)->widget());
    if(frame->frameStyle() == (QFrame::Box | QFrame::Raised))
    {
        qDebug() << "Myframe: " << x << "," <<y << " is a ship";
        return true;
    }
    return false;
}

MyFrame* BattlefieldController::setMiss(MyFrame* frame)
{
    frame->setFrameStyle(QFrame::Box | QFrame::Plain);
    return frame;
}

MyFrame* BattlefieldController::setHit(MyFrame* frame)
{
    frame->setFrameStyle(QFrame::Box | QFrame::Sunken);
    return frame;
}
