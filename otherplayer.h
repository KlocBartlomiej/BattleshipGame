#ifndef OTHERPLAYER_H
#define OTHERPLAYER_H

#include "opponent.h"

#include <tuple>
#include <QTcpSocket>

class OtherPlayer : public Opponent
{
    bool _isPlayerReady;
    QTcpSocket* socket;
public:
    OtherPlayer();

    bool hasOpponentLost();

    std::optional<std::list<std::tuple<int,int>>> takeShot(int,int);
    std::tuple<int,int> getShot();

    void hasMyLastShotHit(const bool);
    void hasMyLastShotSunken(std::optional<std::list<std::tuple<int,int>>>);

    void setPlayerReady(const bool);
    void setSocket(QTcpSocket*);
    bool isPlayerReady();
};

#endif // OTHERPLAYER_H
