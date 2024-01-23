#ifndef SHIPSETTER_H
#define SHIPSETTER_H

#include <QObject>

class ShipSetter : public QObject
{
    Q_OBJECT
    bool isPlaceCapableOfHoldingShip;
    int xLastHovered, yLastHovered;
    int xDrawingDirection, yDrawingDirection;
public:
    ShipSetter();
    void battlefieldClickOn(int, int);
    void battlefieldHoveredOn(int, int);
    void enemyBattlefieldClickOn(int, int);
};

#endif // SHIPSETTER_H
