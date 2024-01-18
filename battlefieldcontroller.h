#ifndef BATTLEFIELDCONTROLLER_H
#define BATTLEFIELDCONTROLLER_H

#include <QGridLayout>
#include <QFrame>

//TODO create it's own file for MyFrame class
class MyFrame : public QFrame{
    int x,y;
public:
    MyFrame(int x, int y): x(x), y(y){ this->setMouseTracking(true);};
    int getX(){ return x; }
    int getY(){ return y; }
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
};

class BattlefieldController
{
    QGridLayout* battlefield;
    QGridLayout* enemyBattlefield;

public:
    MyFrame* setNew(MyFrame*);
    MyFrame* setEmpty(MyFrame*);
    MyFrame* setShip(MyFrame*);
    MyFrame* setMiss(MyFrame*);
    MyFrame* setHit(MyFrame*);
    BattlefieldController(QGridLayout*, QGridLayout*);
};

#endif // BATTLEFIELDCONTROLLER_H
