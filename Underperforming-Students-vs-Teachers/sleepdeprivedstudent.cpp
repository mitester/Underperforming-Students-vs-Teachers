#include "sleepdeprivedstudent.h"
#include "game.h"
#include <QDebug>

const QString SleepDeprivedStudent::DEFAULT_NAME = "Sleep Deprived Student";
QPixmap* SleepDeprivedStudent::PIC_0 = nullptr;
QPixmap* SleepDeprivedStudent::PIC_1 = nullptr;
QPixmap* SleepDeprivedStudent::PIC_2 = nullptr;

SleepDeprivedStudent::SleepDeprivedStudent(QLabel* widget, Row* row, QString name, int maxHp, int skillSpeed, int cost, int damage)
    : AttackStudent(widget, row, name, maxHp, skillSpeed, cost, damage)
{
}

TimeVariant::Type SleepDeprivedStudent::getType() const {return TimeVariant::Type::SLEEP_DEPRIVED_STUDENT;}

void SleepDeprivedStudent::update()
{
    //there is at least one teacher approaching
    //this is just the basic version of implementation of every attack student
    if(row->getLeftMostTeacher())
    {
        if(timeConcept == skillSpeed / 2)
        {
            widget->setPixmap(*PIC_1);
        }
        else if(timeConcept == skillSpeed)
        {
            widget->setPixmap(*PIC_2);
            row->addAssignment(this, damage);
            player->play();
            timeConcept = 0;
        }
        timeConcept += Game::BASIC_TIME_UNIT;
    }
    else
    {
        timeConcept = 0;
        widget->setPixmap(*PIC_0);
    }
}
