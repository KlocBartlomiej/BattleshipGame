#include "ship.h"

Ship::Ship(){}

void Ship::addShipMast(const std::tuple<int,int> shipMast)
{
    ship.push_front(shipMast);
}

bool Ship::searchAndRemove(const std::tuple<int,int> shipMast)
{
    auto it = std::find(ship.begin(), ship.end(), shipMast);
    if(it != ship.end())
    {
        ship.erase(it);
        return true;
    }
    return false;
}

bool Ship::isShipSunken()
{
    return ship.empty();
}
