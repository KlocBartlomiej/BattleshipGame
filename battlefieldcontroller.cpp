#include "battlefieldcontroller.h"
#include <QDebug>

BattlefieldController::BattlefieldController(QGridLayout* battlefield, QGridLayout* enemyBattlefield, QTextEdit *textEdit, const bool isGameStarted)
    :battlefield(battlefield)
    , enemyBattlefield(enemyBattlefield)
    , shipSetter(new ShipSetter(battlefield,true))
    , gameInstance(new GameLogic(battlefield,enemyBattlefield,isGameStarted))
    , connectionToPlayer(new ConnectionToPlayer(textEdit))
{
    QObject::connect(shipSetter, &ShipSetter::shipsAreSet, gameInstance, &GameLogic::playerShipsAreReady);
    QObject::connect(connectionToPlayer, &ConnectionToPlayer::playerConnected, gameInstance, &GameLogic::newPlayerConnected);
}

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
