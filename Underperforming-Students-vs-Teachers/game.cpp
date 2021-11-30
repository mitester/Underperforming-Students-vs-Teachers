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


//default value for Game static variables
Game* Game::instance = nullptr; //save the only instance
QPoint Game::REDBULL_POS = {}; //save the position of redbull place which redbulls need to go
QPixmap* Game::GAME_SCENE_FAIL = nullptr; //will preload the fail game_scene in GameWindow
QPixmap* Game::GAME_SCENE_PASS = nullptr; //will preload the pass game_scene in GameWindow

//default game name for this game
const QString Game::GAME_NAME = "Underperforming Students VS Teachers";
QSize Game::currentSize; //save the current window size of this game

//deprecated since we will use the move with absolute coordinates
void Game::move(QWidget *w, double xPercent, double yPercent) {
    w->move(xPercent / 100.0 * currentSize.width(), yPercent / 100.0 * currentSize.height());
}

//constructor
Game::Game(QWidget* parent) : QObject(parent), parent(parent)
{
    currentSize = parent->size(); //save the size of parent


    currentTimeLeft = QTime(0, 0); //initialize the currentTimeLeft by 0h 0m
    currentTimeLeft = currentTimeLeft.addMSecs(GAME_DURATION); //add GAME_DURATION milliseconds

    //initialize the timer
    mainTimer = new QTimer(parent);
    mainTimer->setInterval(BASIC_TIME_UNIT); //set it to emit timeout() per BASIC_TIME_UNIT

    //it bounds with the slot which guards the game progress
    mainTimer->callOnTimeout(this, &Game::update);

    //generatingTimer is for generating teachers
    generatingTimer = new QTimer(parent);
    generatingTimer->setInterval(getRandomInterval());
    generatingTimer->callOnTimeout(this, &Game::generateTeacher); //binds Game::generateTeacher() with timeout() using signals and slots


    //initialize the 4 rows object
    for(int i = 0; i < NUMBER_OF_ROW; i++)
        rows[i] = new Row(i, GRID_UP + i*GRID_INTERVAL_VERTICAL,NUMBER_OF_COLUMN,parent);

    //sets the bgm resource file to play after it starts
    player.setMedia(QUrl("qrc:/sounds/bgm.mp3"));

    //sentinels act as the widget layer split
    //it divdes layers
    for(int i = 0; i < NUMBER_OF_ROW - 1; i++)
    {
        sentinels[i] = new QWidget(parent);
        sentinels[i]->setGeometry(0,0,0,0);
    }
}

//destructor
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

//add n Redbull
//return true if it adds successfully
//return false if it failed
bool Game::addRedbull(int n)
{
    int temp = redbullNum + n;

    if(temp < 0) return false;

    redbullNum = temp;
    emit notifyAddRedbull();
    return true;
}

//binds update() of timeVariant with timeout() of mainTimer
//since Qt implements dynamic binding. The update() function of the corresponding class is called
void Game::registerTimeVariant(TimeVariant *timeVariant)
{
    mainTimer->callOnTimeout(timeVariant, &TimeVariant::update);
}

//return the Row object at the index i
Row* Game::getRowAt(int i) const
{
    return rows[i];
}

//it starts the game
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

//it pauses the game
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

//it is also binded with mainTimer
void Game::update()
{
    //if the game has ended
    if(checkTerminated())
    {
        pause(); //pause the game immediately cuz nobody should move

        //initialization of game_ended label
        QLabel* lb_game_ended = new QLabel(parent);
        lb_game_ended->setScaledContents(true);
        lb_game_ended->setGeometry(GAME_ENDED_LABEL_X, GAME_ENDED_LABEL_Y,
                                   GAME_ENDED_LABEL_WIDTH, GAME_ENDED_LABEL_HEIGHT);
        lb_game_ended->setPixmap(QPixmap());
        lb_game_ended->hide();

        //if student has won
        if(gameStatus == GameStatus::STUDENT_WON)
        {
            lb_game_ended->setPixmap(*GAME_SCENE_PASS); //show the game won label
            player.setMedia(QUrl("qrc:/sounds/victory.mp3")); //play the victory sound
            player.play();
        }
        //if teacher won
        else if(gameStatus == GameStatus::TEACHER_WON)
        {
            lb_game_ended->setPixmap(*GAME_SCENE_FAIL); //show the game lose label
            player.setMedia(QUrl("qrc:/sounds/lose.mp3")); //play the lose sound
            player.play();

        }
        lb_game_ended->raise(); //raise the label
        lb_game_ended->show(); //show the label
    }

    //get the milliseconds passed
    int msecs = GAME_DURATION - currentTimeLeft.msecsSinceStartOfDay();
    currentTimeLeft = currentTimeLeft.addMSecs(-Game::BASIC_TIME_UNIT); //decreasing currentTimeLeft
    if(msecs <= GAME_DURATION * 1/4) //when the game passed 1/4
    {
        //teacher kind
        generatingTeacherUpperBound = 9;

        //generating time
        generatingTimerLowerBound = 4000;
        generatingTimerUpperBound = 10001;
    }
    else if(msecs <= GAME_DURATION * 1/2) //when the game passed 1/2
    {
        //teacher kind
        generatingTeacherLowerBound = 0;
        generatingTeacherUpperBound = 9;

        //generating time
        generatingTimerLowerBound = 4000;
        generatingTimerUpperBound = 10001;
    }
    else if(msecs <= GAME_DURATION * 3/4) //when the game passed 3/4
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
        {
            rows[rowNum]->addTeacher(TimeVariant::Type::DESMOND);
            desmondRowId = rowNum;
        }

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

    if(rowId == NUMBER_OF_ROW - 1)
    {
        h->getWidget()->raise();
        if(desmond && desmondRowId == rowId) desmond->getWidget()->raise();
    }
    else
    {
        h->getWidget()->stackUnder(sentinels[rowId]);
        if(desmond && desmondRowId == rowId) desmond->getWidget()->stackUnder(sentinels[rowId]);
    }
}
