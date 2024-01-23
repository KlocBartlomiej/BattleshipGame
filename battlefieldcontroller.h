#ifndef BATTLEFIELDCONTROLLER_H
#define BATTLEFIELDCONTROLLER_H

#include <QGridLayout>
#include "shipsetter.h"
#include "myframe.h"

class BattlefieldController
{
    QGridLayout* battlefield;
    QGridLayout* enemyBattlefield;

    ShipSetter* shipSetter;

public:
    MyFrame* setNew(MyFrame*,bool);
    MyFrame* setEmpty(MyFrame*);
    MyFrame* setShip(MyFrame*);
    MyFrame* setMiss(MyFrame*);
    MyFrame* setHit(MyFrame*);

    BattlefieldController(QGridLayout*, QGridLayout*);
};

#endif // BATTLEFIELDCONTROLLER_H
