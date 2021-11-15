#include "game.h"

#include <QTimer>

Game::Game(QObject* parent) : QObject(parent)
{
    timer = new QTimer(parent);
    timer->start(BASIC_TIME_UNIT);
}

int Game::getRedbullNum() const {return redbullNum;}

bool Game::addRedbull(int n)
{
    int temp = redbullNum + n;
    if(temp < 0) return false;
    redbullNum = temp;
    return true;
}

void Game::registerTimeVariant(TimeVariant *timeVariant)
{
    timer->callOnTimeout(timeVariant, &TimeVariant::update);
}
