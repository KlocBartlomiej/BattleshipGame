#include "myframe.h"

void MyFrame::setNew()
{
    this->setLineWidth(3);
    this->setMidLineWidth(3);
    this->setFrameStyle(QFrame::Panel | QFrame::Raised);
}

void MyFrame::setHiddenShip(const int x,const int y,const QGridLayout* battlefield)
{
    MyFrame* frame = qobject_cast<MyFrame*>(battlefield->itemAtPosition(x,y)->widget());
    frame->isShipHidden = true;
}


void MyFrame::setShipNeighbour(const int x,const int y,const QGridLayout* battlefield)
{
    MyFrame* frame = qobject_cast<MyFrame*>(battlefield->itemAtPosition(x,y)->widget());
    frame->isShipNeighbour = true;
}

bool MyFrame::isNeighbourFrame(const int x,const int y,const QGridLayout* battlefield)
{
    MyFrame* frame = qobject_cast<MyFrame*>(battlefield->itemAtPosition(x,y)->widget());
    return frame->isShipNeighbour;
}

void MyFrame::setEmpty(const int x,const int y,const QGridLayout* battlefield)
{
    MyFrame* frame = qobject_cast<MyFrame*>(battlefield->itemAtPosition(x,y)->widget());
    frame->setFrameStyle(QFrame::Panel | QFrame::Raised);
    frame->isShipHidden = false;
    frame->isShipNeighbour = false;
}

void MyFrame::setShip(const int x,const int y,const QGridLayout* battlefield)
{
    MyFrame* frame = qobject_cast<MyFrame*>(battlefield->itemAtPosition(x,y)->widget());
    frame->setFrameStyle(QFrame::Box | QFrame::Raised);
}

bool MyFrame::isShip(const int x,const int y,const QGridLayout* battlefield)
{
    MyFrame* frame = qobject_cast<MyFrame*>(battlefield->itemAtPosition(x,y)->widget());
    if(frame->isShipHidden || frame->frameStyle() == (QFrame::Box | QFrame::Raised))
    {
        qDebug() << "Myframe: " << x << "," <<y << " is a ship";
        return true;
    }
    return false;
}

void MyFrame::setMiss(const int x,const int y, const QGridLayout* enemyBattlefield)
{
    MyFrame* frame = qobject_cast<MyFrame*>(enemyBattlefield->itemAtPosition(x,y)->widget());
    frame->setFrameStyle(QFrame::Box | QFrame::Plain);
}

void MyFrame::setHit(const int x,const int y,const QGridLayout* enemyBattlefield)
{
    MyFrame* frame = qobject_cast<MyFrame*>(enemyBattlefield->itemAtPosition(x,y)->widget());
    frame->setFrameStyle(QFrame::Box | QFrame::Sunken);
}

bool MyFrame::isHit(const int x,const int y,const QGridLayout* battlefield)
{
    MyFrame* frame = qobject_cast<MyFrame*>(battlefield->itemAtPosition(x,y)->widget());
    if(frame->frameStyle() == (QFrame::Box | QFrame::Sunken))
    {
        qDebug() << "Myframe: " << x << "," <<y << " is a hit";
        return true;
    }
    return false;
}
