#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <QGridLayout>
#include <QObject>

#include "opponent.h"
#include "ship.h"
#include "myframe.h"

class GameLogic : public QObject
{
    Q_OBJECT

    int playersSunkenShips;
    int enemysSunkenShips;
    QGridLayout* playerBattlefield;
    std::list<Ship> ships;
    std::list<std::tuple<int,int>> shotsFired;
    Opponent* opponent;

    bool isGameStarted;
    void gameFinished(const QString);

public:
    GameLogic(QGridLayout*, const bool);

    void gameStarted();
    bool hasGameStarted();

    void startPlaying();
    void setOpponentInstance(Opponent*);

    void hasMyLastShotHit(const bool);
    void hasMyLastShotSunken(const bool);

public slots:
    void playerShipsAreReady(std::list<Ship>);
    void enemyBattlefieldClickOn(const int, const int);

signals:
    void gameEnded(const QString);
};

#endif // GAMELOGIC_H
