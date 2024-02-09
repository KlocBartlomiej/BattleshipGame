#ifndef MYFRAME_H
#define MYFRAME_H

#include <QFrame>
#include <QGridLayout>

class MyFrame : public QFrame{
    Q_OBJECT
    int x,y;
    bool isShipHidden;
    bool isShipNeighbour;
public:
    MyFrame(int x, int y): x(x), y(y), isShipHidden(false), isShipNeighbour(false){ this->setMouseTracking(true);}
    int getX(){ return x; }
    int getY(){ return y; }
    void mousePressEvent(QMouseEvent* event){ emit clickedOn(x,y);}
    void mouseMoveEvent(QMouseEvent* event){ emit hoveredOn(x,y);}

    void setNew();
    static void setHiddenShip(const int,const int,const QGridLayout*);
    static void setShipNeighbour(const int,const int,const QGridLayout*);
    static bool isNeighbourFrame(const int,const int,const QGridLayout*);
    static void setEmpty(const int,const int,const QGridLayout*);
    static void setShip(const int,const int,const QGridLayout*);
    static bool isShip(const int,const int,const QGridLayout*);
    static void setMiss(const int,const int,const QGridLayout*);
    static void setHit(const int,const int,const QGridLayout*);
    static bool isHit(const int,const int,const QGridLayout*);

 signals:
    void clickedOn(int x, int y);
    void hoveredOn(int x, int y);
};

#endif // MYFRAME_H
