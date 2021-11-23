#include "game.h"
#include "cgagod.h"
#include "gbusstudent.h"
#include "shamelessstudent.h"
#include "sleepdeprivedstudent.h"
#include "deadlinefighter.h"
#include "teacherspet.h"

#include "overworkedta.h"
#include "kelvin.h"
#include "pang.h"
#include "desmond.h"

#include <QTimer>
#include <QRandomGenerator>
#include <QProgressBar>
#include <QDebug>


//default value for Game::instance
Game* Game::instance = nullptr;

const QString Game::GAME_NAME = "Underperforming Students VS Teachers";
QSize Game::currentSize;
TimeVariant::Type Game::selectedSprite = TimeVariant::Type::REDBULL;

void Game::move(QWidget *w, double xPercent, double yPercent) {
    w->move(xPercent / 100.0 * currentSize.width(), yPercent / 100.0 * currentSize.height());
}

Game::Game(QWidget* parent) : QObject(parent), parent(parent)
{
    currentSize = parent->size(); //save the size of parent

    mainTimer = new QTimer(parent);
    mainTimer->setInterval(BASIC_TIME_UNIT);

    //it bounds with the slot which guards the game progress
    mainTimer->callOnTimeout(this, &Game::update);

    generatingTimer = new QTimer(parent);
    generatingTimer->setInterval(getRandomInterval());
    generatingTimer->callOnTimeout(this, &Game::generateTeacher);


    for(int i = 0; i < NUMBER_OF_ROW; i++)
        rows[i] = new Row(GRID_UP + i*GRID_INTERVAL_VERTICAL,NUMBER_OF_COLUMN,parent);
}

Game::~Game()
{
    instance = nullptr;
}

//parent will be ignored if instance exists
Game* Game::getInstance(QWidget *parent)
{
    if(instance) return instance;
    instance = new Game(parent);
    return instance;
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
    mainTimer->callOnTimeout(timeVariant, &TimeVariant::update);
}

Row* Game::getRowAt(int i) const
{
    return rows[i];
}

bool Game::start()
{
    if(isStart) return false; //game is unable to re-start

    //game start init
    mainTimer->start();
    generatingTimer->start();
    isStart = true;
    gameStatus = Game::GameStatus::BATTLING;

    return true;
}

bool Game::pause()
{
    if(!isStart) return false; //game is unable to pause if not started

    mainTimer->stop(); //timer will not reset after stop(). Therefore, it is a pause.
    isStart = false;
    gameStatus = Game::GameStatus::PAUSED;
    return true;
}

void Game::update()
{
    if(checkTerminated())
    {
        pause(); //pause the game immediately cuz nobody should move
        //some dialog should pop up afterwards
    }
    //TODO: change the progress bar value
}

bool Game::checkTerminated()
{
    for(int i = 0; i < NUMBER_OF_ROW; i++)
    {
        if(rows[i]->hasReachedEnd()) //teacher cleared one row
        {
            gameStatus = GameStatus::TEACHER_WON;
            return true;
        }
    }

    if(false) //TODO: student cleared all teacher
    {
        gameStatus = GameStatus::STUDENT_WON;
        return true;
    }
    return false;
}

int Game::getRandomInterval() const
{
    return QRandomGenerator::securelySeeded().bounded(generatingTimerLowerBound, generatingTimerUpperBound);
}

Game::GameStatus Game::getGameStatus() const
{
    return gameStatus;
}

void Game::setGameStatus(GameStatus status)
{
    gameStatus = status;
}

void Game::generateTeacher()
{
    int num = QRandomGenerator::securelySeeded().bounded(generatingTeacherLowerBound, generatingTeacherUpperBound);
    int rowNum = QRandomGenerator::securelySeeded().bounded(0, NUMBER_OF_ROW);
    if(num >= 0 && num <= 4)
    {
        rows[rowNum]->addTeacher(TimeVariant::Type::OVERWORKED_TA);
    }
    if(num >= 5 && num <= 6)
    {
        rows[rowNum]->addTeacher(TimeVariant::Type::KELVIN);
    }
    if(num >= 7 && num <= 8)
    {
        rows[rowNum]->addTeacher(TimeVariant::Type::PANG);
    }
    if(num == 9)
    {
        rows[rowNum]->addTeacher(TimeVariant::Type::DESMOND);
    }
    generatingTimer->setInterval(getRandomInterval());
}

QWidget* Game::getParent() const
{
    return parent;
}

void Game::setParent(QObject *parent)
{
    QObject::setParent(parent);
}







