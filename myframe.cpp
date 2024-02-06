#include "myframe.h"

void MyFrame::setNew()
{
    this->setLineWidth(3);
    this->setMidLineWidth(3);
    this->setFrameStyle(QFrame::Panel | QFrame::Raised);
}

void MyFrame::setEmpty(int x, int y, QGridLayout* battlefield)
{
    MyFrame* frame = qobject_cast<MyFrame*>(battlefield->itemAtPosition(x,y)->widget());
    frame->setFrameStyle(QFrame::Panel | QFrame::Raised);
}

void MyFrame::setShip(int x, int y, QGridLayout* battlefield)
{
    MyFrame* frame = qobject_cast<MyFrame*>(battlefield->itemAtPosition(x,y)->widget());
    frame->setFrameStyle(QFrame::Box | QFrame::Raised);
}

bool MyFrame::isShip(int x, int y, QGridLayout* battlefield)
{
    MyFrame* frame = qobject_cast<MyFrame*>(battlefield->itemAtPosition(x,y)->widget());
    if(frame->frameStyle() == (QFrame::Box | QFrame::Raised))
    {
        qDebug() << "Myframe: " << x << "," <<y << " is a ship";
        return true;
    }
    return false;
}

void MyFrame::setMiss(int x, int y, QGridLayout* enemyBattlefield)
{
    MyFrame* frame = qobject_cast<MyFrame*>(enemyBattlefield->itemAtPosition(x,y)->widget());
    frame->setFrameStyle(QFrame::Box | QFrame::Plain);
}

void MyFrame::setHit(int x, int y, QGridLayout* enemyBattlefield)
{
    MyFrame* frame = qobject_cast<MyFrame*>(enemyBattlefield->itemAtPosition(x,y)->widget());
    frame->setFrameStyle(QFrame::Box | QFrame::Sunken);
}

bool MyFrame::isHit(int x, int y, QGridLayout* battlefield)
{
    MyFrame* frame = qobject_cast<MyFrame*>(battlefield->itemAtPosition(x,y)->widget());
    if(frame->frameStyle() == (QFrame::Box | QFrame::Sunken))
    {
        qDebug() << "Myframe: " << x << "," <<y << " is a hit";
        return true;
    }
    return false;
}
