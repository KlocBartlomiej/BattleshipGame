#ifndef BATTLEFIELDCONTROLLER_H
#define BATTLEFIELDCONTROLLER_H

#include <QGridLayout>
#include "shipsetter.h"
#include "myframe.h"
#include "gamelogic.h"

class BattlefieldController
{
    QGridLayout* battlefield;
    QGridLayout* enemyBattlefield;

public:
    BattlefieldController(QGridLayout*, QGridLayout*,const bool);

    ShipSetter* shipSetter;
    GameLogic* gameInstance;
    MyFrame* setNew(MyFrame*,bool);
};

#endif // BATTLEFIELDCONTROLLER_H
