#include "shipsetter.h"
#include <QDebug>

ShipSetter::ShipSetter(QGridLayout * battlefield, const bool makeChangesInUI)
    :battlefield(battlefield)
    , makeChangesInUI(makeChangesInUI)
    , numberOfShipMasts{}{}

void ShipSetter::changeDrawingDirection()
{
    std::swap(this->xDrawingDirection,this->yDrawingDirection);
}

void ShipSetter::setAllShips()
{
    numberOfShipMasts = {4,3,3,2,2,2,1,1,1,1};
}

bool ShipSetter::isPlaceCapableOfHoldingShip(const int x, const int y)
{
    if((xDrawingDirection and numberOfShipMasts.front() + x - 1 > 10) or
       (yDrawingDirection and numberOfShipMasts.front() + y - 1 > 10))
    {
        return false;
    }
    return true;
}

bool ShipSetter::isPlaceNotColidingWithOtherShip(const int x, const int y)
{
    //TODO maybe it's possible to avoid using if(drawingDirection)
    if(xDrawingDirection)
    {
        for(int i=x; i<numberOfShipMasts.front()+x; i++)
        {
            if(MyFrame::isShip(i,y,battlefield))
            {
                return false;
            }
        }
    }
    else
    {
        for(int i=y; i<numberOfShipMasts.front()+y; i++)
        {
            if(MyFrame::isShip(x,i,battlefield))
            {
                return false;
            }
        }
    }
    return true;
}

void ShipSetter::battlefieldClickOn(const int x, const int y)
{
    if(numberOfShipMasts.empty()) { return; }
    qDebug() << "battlefield clicked at " << x << " " << y;

    if(!temporary.empty())
    {
        numberOfShipMasts.pop_front();
        Ship ship = Ship();

        for(std::tuple<int,int> mast : temporary)
        {
            ship.addShipMast(mast);
        }
        ships.push_back(ship);
        temporary.clear();
    }

    if(numberOfShipMasts.empty())
    {
        emit shipsAreSet(getShips());
    }
}

void ShipSetter::clearListAndUiFromLastMove()
{
    qDebug() << "Clearing UI and temporary";
    std::tuple<int, int> point;
    while(!temporary.empty())
    {
        point = temporary.front();
        MyFrame::setEmpty(std::get<0>(point),std::get<1>(point),battlefield);
        qDebug() << "Removing element " << std::get<0>(point) << " " << std::get<1>(point);
        temporary.pop_front();
    }
}

void ShipSetter::battlefieldHoveredOn(const int x, const int y)
{
    if(numberOfShipMasts.empty()) { return; }
    if(xLastHovered == x and yLastHovered == y) { return; }
    qDebug() << "battlefield hovered at " << x << " " << y;

    xLastHovered = x;
    yLastHovered = y;

    if(!temporary.empty()) { clearListAndUiFromLastMove(); }

    if(isPlaceCapableOfHoldingShip(x,y) and isPlaceNotColidingWithOtherShip(x,y))
    {
        if(xDrawingDirection)
        {
            for(int i=x; i<numberOfShipMasts.front()+x; i++)
            {
                qDebug() << "     i = " << i << ", y = " << y;
                temporary.push_back(std::make_tuple(i,y));
                setShip(i,y,battlefield);
            }
        }
        else
        {
            for(int i=y; i<numberOfShipMasts.front()+y; i++)
            {
                qDebug() << "     x = " << x << ", i = " << i;
                temporary.push_back(std::make_tuple(x,i));
                setShip(x,i,battlefield);
            }
        }
    }
    qDebug() << "temporary size: " << temporary.size();
}

void ShipSetter::setShip(int x, int y, QGridLayout* battlefield)
{
    if(makeChangesInUI)
    {
        MyFrame::setShip(x,y,battlefield);
    }
    else
    {
        MyFrame::setHiddenShip(x,y,battlefield,true);
    }
}

std::list<Ship> ShipSetter::getShips()
{
    return ships;
}

void ShipSetter::clearShips()
{
    ships.clear();
}
