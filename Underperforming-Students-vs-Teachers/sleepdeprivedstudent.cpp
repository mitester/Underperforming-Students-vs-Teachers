#include "sleepdeprivedstudent.h"
#include "game.h"

const QString SleepDeprivedStudent::DEFAULT_NAME = "Sleep Deprived Student";

SleepDeprivedStudent::SleepDeprivedStudent(QLabel* widget, Row* row, QString name, int maxHp, double skillSpeed, int cost, int damage)
    : AttackStudent(widget, row, name, maxHp, skillSpeed, cost, damage)
{
    widget->setPixmap(QPixmap(":/images/students/stu_sleep_0.png"));
}

TimeVariant::Type SleepDeprivedStudent::getType() const {return TimeVariant::Type::SLEEP_DEPRIVED_STUDENT;}

void SleepDeprivedStudent::update()
{

}
