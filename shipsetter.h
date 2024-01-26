#ifndef SHIPSETTER_H
#define SHIPSETTER_H

#include <QGridLayout>
#include <QObject>

class ShipSetter : public QObject
{
    Q_OBJECT

    QGridLayout* battlefield;

    int xLastHovered = 0, yLastHovered = 0;
    int xDrawingDirection = 0, yDrawingDirection = 1;

    bool isPlaceCapableOfHoldingShip(int, int);
    bool isPlaceNotColidingWithOtherShip(int, int);

public:
    ShipSetter(QGridLayout*);

    void changeDrawingDirection();

public slots:
    void battlefieldClickOn(int, int);
    void battlefieldHoveredOn(int, int);
};

#endif // SHIPSETTER_H
