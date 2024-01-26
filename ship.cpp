#include "ship.h"

Ship::Ship(int shipMasts)
    :ship(shipMasts){}

void Ship::addShipMast(const std::tuple<int,int> shipMast)
{
    ship.append(shipMast);
}

bool Ship::searchAndRemove(const std::tuple<int,int> shipMast)
{
    if(ship.contains(shipMast))
    {
        ship.removeOne(shipMast);
        return true;
    }
    return false;
}

bool Ship::isShipSunken()
{
    return ship.empty();
}
