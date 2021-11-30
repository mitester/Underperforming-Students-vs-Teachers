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

//add n Redbull (default n is Redbull:DEFAULT_ENERGY)
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

// it starts the game
// return true if successfully start
// otherwise, false
bool Game::start()
{
    if(gameStatus != GameStatus::PAUSED) return false; //game is unable to re-start

    //game start init
    mainTimer->start(); //start to count time
    generatingTimer->start(); //start to generate teachers
    gameStatus = GameStatus::BATTLING; //mark the status to battling
    player.play(); //start to play bgm
    return true; //return true if successfully starts
}

// it pauses the game
// return true if successfully paused
// return false otherwise
bool Game::pause()
{
    if(gameStatus == GameStatus::PAUSED) return false; //game is unable to pause if not started

    mainTimer->stop(); //timer will not reset after stop(). Therefore, it is a pause.
    generatingTimer->stop();

    // if it is battling, it turns to paused
    // the other cases are TEACHER_WON & STUDENT_WON
    // shouldn't change the status if they're the current status
    // but still let them pause the game
    if(gameStatus == GameStatus::BATTLING)
    {
        gameStatus = GameStatus::PAUSED;
    }
    player.pause(); //stop playing the bgm
    return true; //return true if successfully starts
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
        lb_game_ended->setPixmap(QPixmap()); //set it will a empty pixmap
        lb_game_ended->hide(); //set it to be unseen

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
        lb_game_ended->show(); //show the label
        lb_game_ended->raise(); //raise the label so that it's on the top layer
    }

    //if current time left is greater than 0
    if(currentTimeLeft.msecsSinceStartOfDay() > 0)
        currentTimeLeft = currentTimeLeft.addMSecs(-Game::BASIC_TIME_UNIT); //decreasing currentTimeLeft

    int msecs = currentTimeLeft.msecsSinceStartOfDay(); //how much time left in milliseconds

    //using interval notation for the following range explanation
    if(msecs >= GAME_DURATION * 3/4) // [3/4, 4/4)
    {
        //teacher kind
        generatingTeacherUpperBound = 9;

        //generating time
        generatingTimerLowerBound = 4000;
        generatingTimerUpperBound = 10001;
    }
    else if(msecs >= GAME_DURATION * 1/2) //[2/4, 3/4]
    {
        //teacher kind
        generatingTeacherLowerBound = 0;
        generatingTeacherUpperBound = 9;

        //generating time
        generatingTimerLowerBound = 4000;
        generatingTimerUpperBound = 10001;
    }
    else if(msecs >= GAME_DURATION * 1/4) //[1/4, 2/4]
    {
        //teacher kind
        generatingTeacherUpperBound = 20;
        generatingTeacherLowerBound = 4;

        //generating time
        generatingTimerLowerBound = 2000;
        generatingTimerUpperBound = 6001;
    }
    else                                  //(0, 1/4]
    {
        generatingTeacherUpperBound = 20;
        generatingTeacherLowerBound = 10;

        generatingTimerLowerBound = 1000;
        generatingTimerUpperBound = 2001;
    }
}

// it checks if the game has ended
// the criteria are either student won or teacher won
// return true if it is ended
// false otherwise
bool Game::checkTerminated()
{

    //if time is up, student won the game
    if(currentTimeLeft == QTime(0,0))
    {
        gameStatus = GameStatus::STUDENT_WON; //mark the status as student won
        return true; //true if ended
    }

    for(int i = 0; i < NUMBER_OF_ROW; i++)
    {
        if(rows[i]->hasReachedEnd()) //a teacher cleared one row
        {
            gameStatus = GameStatus::TEACHER_WON; //mark the status as teacher won
            return true; //true if ended
        }
    }
    return false; //false if not ended
}

int Game::getRandomInterval() const
{
    // generate a random interval for teacher generation
    // since teacher is generated in a random period
    return QRandomGenerator::securelySeeded().bounded(generatingTimerLowerBound, generatingTimerUpperBound);
}

//getter of gameStatus
Game::GameStatus Game::getGameStatus() const
{
    return gameStatus;
}

//setter of gameStatus
void Game::setGameStatus(GameStatus status)
{
    gameStatus = status;
}

//generate per generatingTimer interval
void Game::generateTeacher()
{
    //get a teacher kind with this generator
    int num = QRandomGenerator::securelySeeded().bounded(generatingTeacherLowerBound, generatingTeacherUpperBound);
    //get a row number for which row the teacher is gonna be
    int rowNum = QRandomGenerator::securelySeeded().bounded(0, NUMBER_OF_ROW);

    //determining which kind of teacher should be generated
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
        // for the game balancing purpose, there will be only one desmond in the same time
        // so if there is no desmond, we put a desmond
        // otherwise, nothing to do
        if(!desmond)
        {
            rows[rowNum]->addTeacher(TimeVariant::Type::DESMOND);
            desmondRowId = rowNum;
        }

    }

    //reset another generating teacher interval for the next generation
    generatingTimer->setInterval(getRandomInterval());
}

//getter of parent
QWidget* Game::getParent() const
{
    return parent;
}

//setter of parent
void Game::setParent(QObject *parent)
{
    QObject::setParent(parent);
}

//getter of mainTimer
//for someone outside which is not TimeVariant who wanna binds with its timeout()
QTimer* Game::getMainTimer() const
{
    return mainTimer;
}

//return the current time left in mm:ss
QString Game::getCurrentTimeLeft() const
{
    return currentTimeLeft.toString("mm:ss");
}

//return the current time left in milliseconds
int Game::getCurrentMsLeft() const
{
    return currentTimeLeft.msecsSinceStartOfDay();
}

//get the cost of each student by an enumeration
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

// it is for ui layout stacking management
// it makes the bottom row of Human stacking on the top
// the top row of Human stacking on the bottom
// it fits the general sense of aesthetics
void Game::adjustHumanLayer(Human* h, int rowId)
{
    //if the rowId is out of bound, error msg printed and return
    if(rowId < 0 || rowId > NUMBER_OF_ROW - 1)
    {
        qDebug() << "Game::adjustHumanLayer(Human* h, int rowId): invalid rowId";
        return;
    }

    // if it is the last row, the human should be raised to the top
    // and since Desmond has to be the top of that layer
    // we need to raise Desmond after other widget is raised to the top
    if(rowId == NUMBER_OF_ROW - 1)
    {
        h->getWidget()->raise();
        if(desmond && desmondRowId == rowId) desmond->getWidget()->raise();
    }
    // otherwise, for any row not the bottom one, it should be stacked under the row below
    // and again, Desmond has to be stacked again after some Human in the same row is above him
    else
    {
        h->getWidget()->stackUnder(sentinels[rowId]);
        if(desmond && desmondRowId == rowId) desmond->getWidget()->stackUnder(sentinels[rowId]);
    }
}
