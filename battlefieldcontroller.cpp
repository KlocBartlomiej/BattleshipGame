#include "battlefieldcontroller.h"

BattlefieldController::BattlefieldController(QGridLayout * battlefield, QGridLayout * enemyBattlefield)
    :battlefield(battlefield), enemyBattlefield(enemyBattlefield)
{

}
//battlefield->addWidget(setShip(battlefield->itemAtPosition(i,j))i,j)
MyFrame * BattlefieldController::setNew(MyFrame* frame)
{//new has to be the same as empty, but will set few things which will stay constant
    //QObject::connect(frame, );
    frame->setLineWidth(3);
    frame->setMidLineWidth(3);
    frame->setFrameStyle(QFrame::Panel | QFrame::Raised);
    return frame;
}

MyFrame * BattlefieldController::setEmpty(MyFrame* frame)
{//panel, raised, linewidth 3 midLineWidth 3
    frame->setFrameStyle(QFrame::Panel | QFrame::Raised);
    return frame;
}

MyFrame * BattlefieldController::setShip(MyFrame* frame)
{//box, raised, linewidth 3 midLineWidth 3
    frame->setFrameStyle(QFrame::Box | QFrame::Raised);
    return frame;
}

MyFrame * BattlefieldController::setMiss(MyFrame* frame)
{//box, plain, linewidth 3 midLineWidth 3
    frame->setFrameStyle(QFrame::Box | QFrame::Plain);
    return frame;
}

MyFrame * BattlefieldController::setHit(MyFrame* frame)
{//box, sunken xD, linewidth 3 midLineWidth 3
    frame->setFrameStyle(QFrame::Box | QFrame::Sunken);
    return frame;
}
