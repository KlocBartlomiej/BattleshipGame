#ifndef SHIP_H
#define SHIP_H

#include<iostream>
#include <QList>
#include <list>

class Ship
{
    std::list<std::tuple<int,int>> ship;
public:
    Ship();
    void addShipMast(const std::tuple<int,int>);
    bool searchAndRemove(const std::tuple<int,int>);
    bool isShipSunken();
    //TODO add function which will exclude all neighbors for bot to aim for
};

#endif // SHIP_H
