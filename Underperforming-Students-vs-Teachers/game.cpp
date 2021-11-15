#include "game.h"

#include <QTimer>
#include <QRandomGenerator>

//default value for Game::instance
Game* Game::instance = nullptr;

Game::Game(QObject* parent) : QObject(parent)
{
    timer = new QTimer(parent);
    timer->setInterval(BASIC_TIME_UNIT);

    for(int i = 0; i < NUMBER_OF_ROW; i++)
        rows[i] = new Row(NUMBER_OF_COLUMN, parent);
}

Game::~Game()
{
    for(int i = 0; i < NUMBER_OF_ROW; i++)
        delete rows[i];
    instance = nullptr;
}

//parent will be ignored if instance exists
Game* Game::getInstance(QObject *parent)
{
    return instance ? instance : new Game(parent);
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

bool Game::start()
{
    if(isStart) return false; //game is unable to re-start

    //game start init
    timer->start();
    gameStatus = Game::GameStatus::BATTLING;
    //TODO: generate teachers if Row didn't provide the API

    return true;
}

bool Game::pause()
{
    if(!isStart) return false; //game is unable to pause if not started

    timer->stop(); //timer will not reset after stop(). Therefore, it is a pause.
    gameStatus = Game::GameStatus::PAUSED;
    return true;
}

//TODO
//void Game::checkTerminated()
//{

//}

Game::GameStatus Game::getGameStatus() const
{
    return gameStatus;
}

void Game::setGameStatus(GameStatus status)
{
    gameStatus = status;
}

//Teacher* Game::generateTeacher()
//{
//    QRandomGenerator generator = QRandomGenerator::securelySeeded();
//}



