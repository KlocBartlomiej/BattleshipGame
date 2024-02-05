#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <QObject>

#include "opponent.h"

class GameLogic : public QObject
{
    Q_OBJECT

    Opponent* opponent;

    bool isGameStarted;

public:
    GameLogic(const bool);

    void gameStarted();
    bool hasGameStarted();

    void startPlaying();
    void setOpponentInstance(Opponent*);

public slots:
    void enemyBattlefieldClickOn(const int, const int);
};

#endif // GAMELOGIC_H
