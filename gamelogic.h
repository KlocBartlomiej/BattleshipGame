#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <QGridLayout>
#include <QObject>
#include <QTcpSocket>

#include "opponent.h"
#include "ship.h"
#include "otherplayer.h"
#include "myframe.h"

class GameLogic : public QObject
{
    Q_OBJECT
    using mastList = std::list<std::tuple<int,int>>;
    int playersSunkenShips;
    int enemysSunkenShips;
    QGridLayout* playerBattlefield;
    QGridLayout* enemyBattlefield;
    std::list<Ship> ships;
    mastList shotsFired;
    Opponent* opponent;

    bool isGameStarted;
    void gameFinished(const QString);

public:
    GameLogic(QGridLayout*,QGridLayout*,const bool);

    void gameStarted();
    bool hasGameStarted();

    void startPlaying();
    void setOpponentInstance(Opponent*);

    void hasMyLastShotHit(const bool);
    void hasMyLastShotSunken(std::optional<mastList>);

public slots:
    void playerShipsAreReady(std::list<Ship>);
    void enemyBattlefieldClickOn(const int, const int);
    void newPlayerConnected(QTcpSocket*);

signals:
    void gameEnded(const QString);
};

#endif // GAMELOGIC_H
