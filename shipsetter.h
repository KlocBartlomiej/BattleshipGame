#ifndef SHIPSETTER_H
#define SHIPSETTER_H

#include "ship.h"
#include "myframe.h"

#include <QGridLayout>
#include <QObject>

class ShipSetter : public QObject
{
    Q_OBJECT

    QGridLayout* battlefield;
    std::list<Ship> ships;
    std::list<std::tuple<int,int>> temporary;
    void clearListAndUiFromLastMove();

    bool areShipsSet;
    std::list<int> numberOfShipMasts;

    int xLastHovered = 0, yLastHovered = 0;
    int xDrawingDirection = 0, yDrawingDirection = 1;

    bool isPlaceCapableOfHoldingShip(const int, const int);
    bool isPlaceNotColidingWithOtherShip(const int, const int);
    //TODO add function which will check if ship you're trying to set is not touching other ships

public:
    ShipSetter(QGridLayout*);

    std::list<Ship> getShips();
    void setAllShips();
    void changeDrawingDirection();

public slots:
    void battlefieldClickOn(const int, const int);
    void battlefieldHoveredOn(const int, const int);

signals:
    void shipsAreSet();
};

#endif // SHIPSETTER_H
