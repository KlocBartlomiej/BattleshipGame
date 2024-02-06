#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <QGridLayout>
#include <QObject>

#include "opponent.h"
#include "ship.h"
#include "myframe.h""

class GameLogic : public QObject
{
    Q_OBJECT

    QGridLayout* playerBattlefield;
    std::list<Ship> ships;
    Opponent* opponent;

    bool isGameStarted;

public:
    GameLogic(QGridLayout*, const bool);

    void gameStarted();
    bool hasGameStarted();

    void startPlaying();
    void setOpponentInstance(Opponent*);

public slots:
    void enemyBattlefieldClickOn(const int, const int);
};

#endif // GAMELOGIC_H
