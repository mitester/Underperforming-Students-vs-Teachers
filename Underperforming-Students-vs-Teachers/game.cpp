#include "game.h"

#include <QTimer>

Game::Game()
{
    timer = new QTimer(nullptr);
    timer->start(BASIC_TIME_UNIT);
}

Game::~Game()
{
    delete timer;
}

int Game::getRedbullNum() const {return redbullNum;}

void Game::addRedbull(int n) {redbullNum += n;}

void Game::registerTimeVariant(TimeVariant *timeVariant)
{
    timer->callOnTimeout(timeVariant, &TimeVariant::update);
}
