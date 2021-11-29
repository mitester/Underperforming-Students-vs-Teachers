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

#include <QTime>
#include <QTimer>
#include <QRandomGenerator>
#include <QProgressBar>
#include <QDebug>
#include <QPoint>


//default value for Game::instance
Game* Game::instance = nullptr;
QPoint Game::REDBULL_POS = {};
QPixmap* Game::GAME_SCENE_FAIL = nullptr;
QPixmap* Game::GAME_SCENE_PASS = nullptr;


const QString Game::GAME_NAME = "Underperforming Students VS Teachers";
QSize Game::currentSize;

void Game::move(QWidget *w, double xPercent, double yPercent) {
    w->move(xPercent / 100.0 * currentSize.width(), yPercent / 100.0 * currentSize.height());
}

Game::Game(QWidget* parent) : QObject(parent), parent(parent)
{
    currentSize = parent->size(); //save the size of parent


    currentTimeLeft = QTime(0, 0);
    currentTimeLeft = currentTimeLeft.addMSecs(GAME_DURATION);

    mainTimer = new QTimer(parent);
    mainTimer->setInterval(BASIC_TIME_UNIT);

    //it bounds with the slot which guards the game progress
    mainTimer->callOnTimeout(this, &Game::update);

    generatingTimer = new QTimer(parent);
    generatingTimer->setInterval(getRandomInterval());
    generatingTimer->callOnTimeout(this, &Game::generateTeacher);


    for(int i = 0; i < NUMBER_OF_ROW; i++)
        rows[i] = new Row(i, GRID_UP + i*GRID_INTERVAL_VERTICAL,NUMBER_OF_COLUMN,parent);

    player.setMedia(QUrl("qrc:/sounds/bgm.mp3"));

    for(int i = 0; i < NUMBER_OF_ROW - 1; i++)
    {
        sentinels[i] = new QWidget(parent);
        sentinels[i]->setGeometry(0,0,0,0);

        if(i == 0) sentinels[i]->lower();
        else if(i == NUMBER_OF_ROW - 2) sentinels[i]->raise();
    }
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
    emit notifyAddRedbull();
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
    if(gameStatus != GameStatus::PAUSED) return false; //game is unable to re-start

    //game start init
    mainTimer->start();
    generatingTimer->start();
    gameStatus = GameStatus::BATTLING;
    player.play();
    return true;
}

bool Game::pause()
{
    if(gameStatus == GameStatus::PAUSED) return false; //game is unable to pause if not started

    mainTimer->stop(); //timer will not reset after stop(). Therefore, it is a pause.
    generatingTimer->stop();
    if(gameStatus == GameStatus::BATTLING)
    {
        gameStatus = GameStatus::PAUSED;
    }
    player.pause();
    return true;
}

void Game::update()
{
    if(checkTerminated())
    {
        pause(); //pause the game immediately cuz nobody should move
        //some dialog should pop up afterwards

        QLabel* lb_game_ended = new QLabel(parent);
        lb_game_ended->setScaledContents(true);
        lb_game_ended->setGeometry(GAME_ENDED_LABEL_X, GAME_ENDED_LABEL_Y,
                                   GAME_ENDED_LABEL_WIDTH, GAME_ENDED_LABEL_HEIGHT);
        lb_game_ended->setPixmap(QPixmap());
        lb_game_ended->hide();

        if(gameStatus == GameStatus::STUDENT_WON)
        {
            lb_game_ended->setPixmap(*GAME_SCENE_PASS);
            player.setMedia(QUrl("qrc:/sounds/victory.mp3"));
            player.play();
        }
        else if(gameStatus == GameStatus::TEACHER_WON)
        {
            lb_game_ended->setPixmap(*GAME_SCENE_FAIL);
            player.setMedia(QUrl("qrc:/sounds/lose.mp3"));
            player.play();

        }
        lb_game_ended->raise();
        lb_game_ended->show();
    }

    int msecs = GAME_DURATION - currentTimeLeft.msecsSinceStartOfDay();
    currentTimeLeft = currentTimeLeft.addMSecs(-Game::BASIC_TIME_UNIT);
    if(msecs <= GAME_DURATION * 1/4)
    {
        //teacher kind
        generatingTeacherUpperBound = 9;

        //generating time
        generatingTimerLowerBound = 4000;
        generatingTimerUpperBound = 10001;
    }
    else if(msecs <= GAME_DURATION * 1/2)
    {
        //teacher kind
        generatingTeacherUpperBound = 17;
        generatingTeacherLowerBound = 0;
        generatingTeacherUpperBound = 9;

        //generating time
        generatingTimerLowerBound = 4000;
        generatingTimerUpperBound = 10001;
    }
    else if(msecs <= GAME_DURATION * 3/4)
    {
        //teacher kind
        generatingTeacherUpperBound = 20;
        generatingTeacherLowerBound = 4;

        //generating time
        generatingTimerLowerBound = 2000;
        generatingTimerUpperBound = 6001;
    }
    else
    {
        generatingTeacherUpperBound = 20;
        generatingTeacherLowerBound = 10;

        generatingTimerLowerBound = 1000;
        generatingTimerUpperBound = 2001;
    }
}

bool Game::checkTerminated()
{

    if(currentTimeLeft == QTime(0,0)) //TODO: student cleared all teacher
    {
        gameStatus = GameStatus::STUDENT_WON;
        return true;
    }

    for(int i = 0; i < NUMBER_OF_ROW; i++)
    {
        if(rows[i]->hasReachedEnd()) //teacher cleared one row
        {
            gameStatus = GameStatus::TEACHER_WON;
            return true;
        }
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
    if(num >= 0 && num <= 9)
    {
        rows[rowNum]->addTeacher(TimeVariant::Type::OVERWORKED_TA);
    }
    if(num >= 10 && num <= 13)
    {
        rows[rowNum]->addTeacher(TimeVariant::Type::PANG);
    }
    if(num >= 14 && num <= 17)
    {
        rows[rowNum]->addTeacher(TimeVariant::Type::KELVIN);
    }
    if(num >= 18 && num <= 20)
    {
        if(!desmond)
            rows[rowNum]->addTeacher(TimeVariant::Type::DESMOND);
    }
    generatingTimer->setInterval(getRandomInterval());
    if(desmond) desmond->getWidget()->raise();
}

QWidget* Game::getParent() const
{
    return parent;
}

void Game::setParent(QObject *parent)
{
    QObject::setParent(parent);
}

QTimer* Game::getMainTimer() const
{
    return mainTimer;
}

QString Game::getCurrentTimeLeft() const
{
    return currentTimeLeft.toString("mm:ss");
}

int Game::getCost(TimeVariant::Type student) {
    switch (student) {
    case TimeVariant::Type::CGA_GOD:
        return CgaGod::DEFAULT_COST;
    case TimeVariant::Type::DEADLINE_FIGHTER:
        return DeadlineFighter::DEFAULT_COST;
    case TimeVariant::Type::GBUS_STUDENT:
        return GbusStudent::DEFAULT_COST;
    case TimeVariant::Type::SHAMELESS_STUDENT:
        return ShamelessStudent::DEFAULT_COST;
    case TimeVariant::Type::SLEEP_DEPRIVED_STUDENT:
        return SleepDeprivedStudent::DEFAULT_COST;
    case TimeVariant::Type::TEACHERS_PET:
        return TeachersPet::DEFAULT_COST;
    default:
        qDebug() << "Invalid type passed in to getCost() function.";
        return 0;
    }
}

void Game::adjustHumanLayer(Human* h, int rowId)
{
    if(rowId < 0 || rowId > NUMBER_OF_ROW - 1)
    {
        qDebug() << "Game::adjustHumanLayer(Human* h, int rowId): invalid rowId";
        return;
    }

    if(rowId == 0)
    {
        h->getWidget()->lower();
    }
    else if(rowId == Game::NUMBER_OF_ROW - 1)
    {
        h->getWidget()->raise();
    }
    else
    {
        h->getWidget()->stackUnder(sentinels[rowId - 1]);
    }
}
