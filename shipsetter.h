#ifndef SHIPSETTER_H
#define SHIPSETTER_H

#include <QObject>

class ShipSetter : public QObject
{
    Q_OBJECT
    int xDirection, yDirection;
public:
    ShipSetter();
    void battlefieldClickOn(int, int);
    void battlefieldHoveredOn(int, int);
    void enemyBattlefieldClickOn(int, int);
};

#endif // SHIPSETTER_H
