#ifndef SHIP_H
#define SHIP_H

#include<iostream>
#include <QList>

class Ship
{
    QList<std::tuple<int,int>> ship;
public:
    Ship(int);
    void addShipMast(const std::tuple<int,int>);
    bool searchAndRemove(const std::tuple<int,int>);
    bool isShipSunken();
};

#endif // SHIP_H
