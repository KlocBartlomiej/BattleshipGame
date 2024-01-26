#ifndef BATTLEFIELDCONTROLLER_H
#define BATTLEFIELDCONTROLLER_H

#include <QGridLayout>
#include "shipsetter.h"
#include "myframe.h"

class BattlefieldController
{
    QGridLayout* battlefield;
    QGridLayout* enemyBattlefield;

public:
    BattlefieldController(QGridLayout*, QGridLayout*);

    ShipSetter* shipSetter;
    bool isGameStarted;
    MyFrame* setNew(MyFrame*,bool);
};

#endif // BATTLEFIELDCONTROLLER_H
