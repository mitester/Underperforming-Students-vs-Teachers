#include "sleepdeprivedstudent.h"
#include "game.h"
#include <QDebug>
#include <QThread>

const QString SleepDeprivedStudent::DEFAULT_NAME = "Sleep Deprived Student";

SleepDeprivedStudent::SleepDeprivedStudent(QLabel* widget, Row* row, QString name, int maxHp, int skillSpeed, int cost, int damage)
    : AttackStudent(widget, row, name, maxHp, skillSpeed, cost, damage)
{
}

TimeVariant::Type SleepDeprivedStudent::getType() const {return TimeVariant::Type::SLEEP_DEPRIVED_STUDENT;}

void SleepDeprivedStudent::update()
{
    //there is at least one teacher approaching
    if(row->getLeftMostTeacher())
    {

        if(timeConcept == skillSpeed / 2)
        {
            widget->setPixmap(QPixmap(":/images/students/stu_sleep_1.png"));
        }
        else if(timeConcept == skillSpeed)
        {
            widget->setPixmap(QPixmap(":/images/students/stu_sleep_2.png"));
            row->addAssignment(this, damage);
            timeConcept = 0;
        }
        timeConcept += Game::BASIC_TIME_UNIT;
    }
    else
    {
        timeConcept = 0;
        widget->setPixmap(QPixmap(":/images/students/stu_sleep_0.png"));
    }
}
