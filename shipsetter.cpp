#include "shipsetter.h"
#include <QDebug>

ShipSetter::ShipSetter(QGridLayout * battlefield)
    :battlefield(battlefield){}

void ShipSetter::changeDrawingDirection()
{
    std::swap(this->xDrawingDirection,this->yDrawingDirection);
}

bool ShipSetter::isPlaceCapableOfHoldingShip(int x, int y)
{
    return true;
}

bool ShipSetter::isPlaceNotColidingWithOtherShip(int x, int y)
{
    return true;
}

void ShipSetter::battlefieldClickOn(int x, int y)
{
    qDebug() << "battlefield clicked at " << x << " " << y;
}

void ShipSetter::battlefieldHoveredOn(int x, int y)
{
    qDebug() << "battlefield hovered at " << x << " " << y;
    if(xLastHovered == x and yLastHovered == y) { return; }

    xLastHovered = x;
    yLastHovered = y;
}
