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

#include "redbull.h"
#include "vendingmachine.h"

#include <QTimer>
#include <QRandomGenerator>
#include <QProgressBar>
#include <QDebug>


//default value for Game::instance
Game* Game::instance = nullptr;

const QString Game::GAME_NAME = "Underperforming Students VS Teachers";
QSize Game::currentSize;

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

    SleepDeprivedStudent::PIC_0 = new QPixmap(":/images/students/stu_sleep_0.png");
    SleepDeprivedStudent::PIC_1 = new QPixmap(":/images/students/stu_sleep_1.png");
    SleepDeprivedStudent::PIC_2 = new QPixmap(":/images/students/stu_sleep_2.png");

    CgaGod::PIC_0 = new QPixmap(":/images/students/stu_cga_0.png");
    CgaGod::PIC_1 = new QPixmap(":/images/students/stu_cga_1.png");
    CgaGod::PIC_2 = new QPixmap(":/images/students/stu_cga_2.png");

    GbusStudent::PIC_0 = new QPixmap(":/images/students/stu_gbus_0.png");
    GbusStudent::PIC_1 = new QPixmap(":/images/students/stu_gbus_1.png");
    GbusStudent::PIC_2 = new QPixmap(":/images/students/stu_gbus_2.png");

    ShamelessStudent::PIC_0 = new QPixmap(":/images/students/stu_shameless_0.png");

    TeachersPet::PIC_0 = new QPixmap(":/images/students/stu_pet_0.png");

    DeadlineFighter::PIC_0 = new QPixmap(":/images/students/stu_deadline_0.png");
    DeadlineFighter::PIC_1 = new QPixmap(":/images/students/stu_deadline_1.png");
    DeadlineFighter::PIC_2 = new QPixmap(":/images/students/stu_deadline_2.png");
    DeadlineFighter::PIC_3 = new QPixmap(":/images/students/stu_deadline_3.png");
    DeadlineFighter::PIC_4 = new QPixmap(":/images/students/stu_deadline_4.png");
    DeadlineFighter::PIC_5 = new QPixmap(":/images/students/stu_deadline_5.png");

    OverworkedTA::PIC_0 = new QPixmap(":/images/teachers/tea_overworked_ta_0.png");
    OverworkedTA::PIC_1 = new QPixmap(":/images/teachers/tea_overworked_ta_1.png");
    OverworkedTA::PIC_2 = new QPixmap(":/images/teachers/tea_overworked_ta_2.png");
    OverworkedTA::PIC_3 = new QPixmap(":/images/teachers/tea_overworked_ta_3.png");

    Pang::PIC_0 = new QPixmap(":/images/teachers/tea_pang_0.png");
    Pang::PIC_1 = new QPixmap(":/images/teachers/tea_pang_1.png");
    Pang::PIC_2 = new QPixmap(":/images/teachers/tea_pang_2.png");
    Pang::PIC_3 = new QPixmap(":/images/teachers/tea_pang_3.png");

    Kelvin::PIC_0 = new QPixmap(":/images/teachers/tea_kelvin_0.png");
    Kelvin::PIC_1 = new QPixmap(":/images/teachers/tea_kelvin_1.png");
    Kelvin::PIC_2 = new QPixmap(":/images/teachers/tea_kelvin_2.png");
    Kelvin::PIC_3 = new QPixmap(":/images/teachers/tea_kelvin_3.png");


    Desmond::PIC_0 = new QPixmap(":/images/teachers/tea_desmond_0.png");
    Desmond::PIC_1 = new QPixmap(":/images/teachers/tea_desmond_1.png");
    Desmond::PIC_2 = new QPixmap(":/images/teachers/tea_desmond_2.png");
    Desmond::PIC_3 = new QPixmap(":/images/teachers/tea_desmond_3.png");


    Assignment::PIC_0 = new QPixmap(":/images/items/item_assignment_0.png");

    Redbull::PIC_0 = new QPixmap(":/images/items/item_redbull_0.png");

    VendingMachine::PIC_0 = new QPixmap(":/images/items/item_assignment_0.png");
}

Game::~Game()
{
    instance = nullptr;

    delete SleepDeprivedStudent::PIC_0;
    delete SleepDeprivedStudent::PIC_1;
    delete SleepDeprivedStudent::PIC_2;

    delete CgaGod::PIC_0;
    delete CgaGod::PIC_1;
    delete CgaGod::PIC_2;

    delete GbusStudent::PIC_0;
    delete GbusStudent::PIC_1;
    delete GbusStudent::PIC_2;

    delete ShamelessStudent::PIC_0;

    delete TeachersPet::PIC_0;

    delete DeadlineFighter::PIC_0;
    delete DeadlineFighter::PIC_1;
    delete DeadlineFighter::PIC_2;
    delete DeadlineFighter::PIC_3;
    delete DeadlineFighter::PIC_4;
    delete DeadlineFighter::PIC_5;

    delete OverworkedTA::PIC_0;
    delete OverworkedTA::PIC_1;
    delete OverworkedTA::PIC_2;
    delete OverworkedTA::PIC_3;

    delete Pang::PIC_0;
    delete Pang::PIC_1;
    delete Pang::PIC_2;
    delete Pang::PIC_3;

    delete Kelvin::PIC_0;
    delete Kelvin::PIC_1;
    delete Kelvin::PIC_2;
    delete Kelvin::PIC_3;

    delete Desmond::PIC_0;
    delete Desmond::PIC_1;
    delete Desmond::PIC_2;
    delete Desmond::PIC_3;


    delete Assignment::PIC_0;

    delete Redbull::PIC_0;

    delete VendingMachine::PIC_0;

    //nullptr
    SleepDeprivedStudent::PIC_0 = nullptr;
    SleepDeprivedStudent::PIC_1 = nullptr;
    SleepDeprivedStudent::PIC_2 = nullptr;

    CgaGod::PIC_0 = nullptr;
    CgaGod::PIC_1 = nullptr;
    CgaGod::PIC_2 = nullptr;

    GbusStudent::PIC_0 = nullptr;
    GbusStudent::PIC_1 = nullptr;
    GbusStudent::PIC_2 = nullptr;

    ShamelessStudent::PIC_0 = nullptr;

    TeachersPet::PIC_0 = nullptr;

    DeadlineFighter::PIC_0 = nullptr;
    DeadlineFighter::PIC_1 = nullptr;
    DeadlineFighter::PIC_2 = nullptr;
    DeadlineFighter::PIC_3 = nullptr;
    DeadlineFighter::PIC_4 = nullptr;
    DeadlineFighter::PIC_5 = nullptr;

    OverworkedTA::PIC_0 = nullptr;
    OverworkedTA::PIC_1 = nullptr;
    OverworkedTA::PIC_2 = nullptr;
    OverworkedTA::PIC_3 = nullptr;

    Pang::PIC_0 = nullptr;
    Pang::PIC_1 = nullptr;
    Pang::PIC_2 = nullptr;
    Pang::PIC_3 = nullptr;

    Kelvin::PIC_0 = nullptr;
    Kelvin::PIC_1 = nullptr;
    Kelvin::PIC_2 = nullptr;
    Kelvin::PIC_3 = nullptr;

    Desmond::PIC_0 = nullptr;
    Desmond::PIC_1 = nullptr;
    Desmond::PIC_2 = nullptr;
    Desmond::PIC_3 = nullptr;


    Assignment::PIC_0 = nullptr;

    Redbull::PIC_0 = nullptr;

    VendingMachine::PIC_0 = nullptr;
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
    //int num = QRandomGenerator::securelySeeded().bounded(generatingTeacherLowerBound, generatingTeacherUpperBound);
    int num = QRandomGenerator::securelySeeded().bounded(3, 8);
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







