#include "sleepdeprivedstudent.h"
#include "game.h"
#include <QDebug>

const QString SleepDeprivedStudent::DEFAULT_NAME = "Sleep Deprived Student";

SleepDeprivedStudent::SleepDeprivedStudent(QLabel* widget, Row* row, QString name, int maxHp, int skillSpeed, int cost, int damage)
    : AttackStudent(widget, row, name, maxHp, skillSpeed, cost, damage)
{
    widget->setPixmap(QPixmap(":/images/students/stu_sleep_0.png"));
}

TimeVariant::Type SleepDeprivedStudent::getType() const {return TimeVariant::Type::SLEEP_DEPRIVED_STUDENT;}

void SleepDeprivedStudent::update()
{
    if(row->getLeftMostTeacher()) //there is at least one teacher approaching
    {
        attackMode = (attackMode + 1) % 3;
    }
    else
    {
        attackMode = 0;
    }

    //packing a string to swap pictures
    QString s = QString(":/images/students/stu_sleep_%1.png").arg(attackMode);
    widget->setPixmap(QPixmap(s));

}
