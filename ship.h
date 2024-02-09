#ifndef SHIP_H
#define SHIP_H

#include <list>
#include <tuple>
#include <algorithm>

#include <QGridLayout>

class Ship
{
    std::list<std::tuple<int,int>> ship;
    std::list<std::tuple<int,int>> neighbours;
    void pupulateNeighbourList();
    void removeDuplicatedFromTheList();
    void setNeighboursNotAwailableForShips(const QGridLayout*);
public:
    Ship(const std::list<std::tuple<int,int>>,const QGridLayout*);
    void addShipMast(const std::tuple<int,int>);
    bool searchAndRemove(const std::tuple<int,int>);
    bool isShipSunken();
};

#endif // SHIP_H
