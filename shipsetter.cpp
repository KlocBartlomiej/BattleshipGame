#include "shipsetter.h"
#include <QDebug>

ShipSetter::ShipSetter()
{

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

void ShipSetter::enemyBattlefieldClickOn(int x, int y)
{
    qDebug() << "enemy battlefield clicked at " << x << " " << y;
}
