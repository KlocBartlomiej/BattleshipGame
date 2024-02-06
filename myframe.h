#ifndef MYFRAME_H
#define MYFRAME_H

#include <QFrame>
#include <QGridLayout>

class MyFrame : public QFrame{
    Q_OBJECT
    int x,y;
public:
    MyFrame(int x, int y): x(x), y(y){ this->setMouseTracking(true);}
    int getX(){ return x; }
    int getY(){ return y; }
    void mousePressEvent(QMouseEvent* event){ emit clickedOn(x,y);}
    void mouseMoveEvent(QMouseEvent* event){ emit hoveredOn(x,y);}

    void setNew();
    static void setEmpty(int,int,QGridLayout*);
    static void setShip(int,int,QGridLayout*);
    static bool isShip(int x, int y,QGridLayout*);
    static void setMiss(int,int,QGridLayout*);
    static void setHit(int,int,QGridLayout*);
    static bool isHit(int x, int y,QGridLayout*);

 signals:
    void clickedOn(int x, int y);
    void hoveredOn(int x, int y);
};

#endif // MYFRAME_H
