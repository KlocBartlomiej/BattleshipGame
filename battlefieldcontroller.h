#ifndef BATTLEFIELDCONTROLLER_H
#define BATTLEFIELDCONTROLLER_H

#include <QGridLayout>
#include <QTextEdit>
#include "shipsetter.h"
#include "myframe.h"
#include "gamelogic.h"
#include "connectionToPlayer.h"
#include "otherplayer.h"

class BattlefieldController
{
    QGridLayout* battlefield;
    QGridLayout* enemyBattlefield;

public:
    BattlefieldController(QGridLayout*, QGridLayout*, QTextEdit*, const bool);

    ShipSetter* shipSetter;
    GameLogic* gameInstance;
    ConnectionToPlayer* connectionToPlayer;
    MyFrame* setNew(MyFrame*,bool);
};

#endif // BATTLEFIELDCONTROLLER_H
