#include "game.h"
#include "overworkedta.h"
#include "kelvin.h"
#include "pang.h"
#include "desmond.h"

#include <QTimer>
#include <QRandomGenerator>
#include <QProgressBar>

//default value for Game::instance
Game* Game::instance = nullptr;

Game::Game(QWidget* parent) : QObject(parent), parent(parent)
{
    timer = new QTimer(parent);
    timer->setInterval(BASIC_TIME_UNIT);

    //it bounds with the slot which guards the game progress
    timer->callOnTimeout(this, &Game::update);

    for(int i = 0; i < NUMBER_OF_ROW; i++)
        rows[i] = new Row(NUMBER_OF_COLUMN, parent);
    progressBar = new QProgressBar(parent);

    //evaluate the prob. using the default values
    reCalculateGenerateTeacherProb();
}

Game::~Game()
{
    instance = nullptr;
}

//parent will be ignored if instance exists
Game* Game::getInstance(QWidget *parent)
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

Row* Game::getRowAt(int i) const
{
    return rows[i];
}

bool Game::start()
{
    if(isStart) return false; //game is unable to re-start

    //game start init
    timer->start();
    isStart = true;
    gameStatus = Game::GameStatus::BATTLING;

    //generate teachers for each and add it to rows[i]
    for(int i = 0; i < NUMBER_OF_ROW; i++)
    {
        int num = QRandomGenerator::securelySeeded().bounded(numberOfTeachers.min, numberOfTeachers.max + 1);
        for(int j = 0; j < num; j++)
        {
            rows[i]->addTeacher(generateTeacher());
        }
    }
    return true;
}

bool Game::pause()
{
    if(!isStart) return false; //game is unable to pause if not started

    timer->stop(); //timer will not reset after stop(). Therefore, it is a pause.
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

    if(progressBar->value() >= progressBar->maximum()) //student cleared all teacher
    {
        gameStatus = GameStatus::STUDENT_WON;
        return true;
    }
    return false;
}

Game::GameStatus Game::getGameStatus() const
{
    return gameStatus;
}

void Game::setGameStatus(GameStatus status)
{
    gameStatus = status;
}

void Game::reCalculateGenerateTeacherProb()
{
    generateOverworkedTAEvents.clear();
    generateKelvinEvents.clear();
    generatePangEvents.clear();
    generateDesmondEvents.clear();

    for(int i = 0; i < totalNumberofEvents; i++)
    {
        if(overworkedTAEventsInterval.contains(i))
        {
            generateOverworkedTAEvents.insert(i);
        }
        else if(KelvinEventsInterval.contains(i))
        {
            generateKelvinEvents.insert(i);
        }
        else if(PangEventsInterval.contains(i))
        {
            generatePangEvents.insert(i);
        }
        else if(DesmondEventsInterval.contains(i))
        {
            generateDesmondEvents.insert(i);
        }
    }
}

Teacher* Game::generateTeacher()
{
    //get a securely seeded generator
    QRandomGenerator generator = QRandomGenerator::securelySeeded();

    //bounded() is 0(inclusive) to max(exclusive)
    int num = generator.bounded(totalNumberofEvents);
    if(generateOverworkedTAEvents.contains(num))
        return new OverworkedTA(new QLabel(parent));
    else if(generateKelvinEvents.contains(num))
        return new Kelvin(new QLabel(parent));
    else if(generatePangEvents.contains(num))
        return new Pang(new QLabel(parent));
    else if(generateDesmondEvents.contains(num))
        return new Desmond(new QLabel(parent));

    return nullptr;
}













