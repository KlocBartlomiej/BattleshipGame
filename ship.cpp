#include "myframe.h"
#include "ship.h"

Ship::Ship(const std::list<std::tuple<int,int>> ship, const QGridLayout* battlefield)
    : ship(ship)
{
    pupulateNeighbourList();
    removeDuplicatedFromTheList();
    setNeighboursNotAwailableForShips(battlefield);
}

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

void Ship::pupulateNeighbourList()
{
    int x,y;
    for(std::tuple<int,int> shipMast : ship)
    {
        x = std::get<0>(shipMast);
        y = std::get<1>(shipMast);
        neighbours.push_back(std::make_tuple(x-1,y-1));
        neighbours.push_back(std::make_tuple(x-1,y));
        neighbours.push_back(std::make_tuple(x-1,y+1));
        neighbours.push_back(std::make_tuple(x+1,y-1));
        neighbours.push_back(std::make_tuple(x+1,y));
        neighbours.push_back(std::make_tuple(x+1,y+1));
        neighbours.push_back(std::make_tuple(x,y-1));
        neighbours.push_back(std::make_tuple(x,y+1));
    }
}

void Ship::removeDuplicatedFromTheList()
{
    neighbours.sort();
    neighbours.unique();
    int x,y;
    for(std::tuple<int,int> shipMast : ship)
    {
        auto it = neighbours.begin();
        x = std::get<0>(shipMast);
        y = std::get<1>(shipMast);
        it = std::find(neighbours.begin(),neighbours.end(),std::make_tuple(x,y));
        if(it != neighbours.end())
        {
            neighbours.erase(it);
        }
    }
    auto it = neighbours.begin();
    while(it != neighbours.end())
    {
        x = std::get<0>(*it);
        y = std::get<1>(*it);
        if(x > 10 || y > 10 || x < 1 || y < 1)
        {
            it = neighbours.erase(it);
            continue;
        }
        it++;
    }
}

void Ship::setNeighboursNotAwailableForShips(const QGridLayout* battlefield)
{
    int x,y;
    for(std::tuple<int,int> shipMast : neighbours)
    {
        x = std::get<0>(shipMast);
        y = std::get<1>(shipMast);
        MyFrame::setShipNeighbour(x,y,battlefield);
    }
}
