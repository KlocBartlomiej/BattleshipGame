#include "bot.h"
#include<QDebug>

Bot::Bot()
{
    //TODO how to store bot's battlefield? (bot don't need to have QGridArray, it can store own ships as array of bool)
}

void Bot::takeShot(int,int)
{
    qDebug() << "I'm bot";
}

std::tuple<int,int> Bot::getShot()
{
    if(!nextPossibleShots.empty())
    {
        return std::make_tuple(
            QRandomGenerator::global()->bounded(1, 10),
            QRandomGenerator::global()->bounded(1, 10));
    }
    auto nextShot = nextPossibleShots.front();
    nextPossibleShots.pop_front();
    return nextShot;
}
