#include "sleepdeprivedstudent.h"

const QString SleepDeprivedStudent::defaultName = "Sleep Deprived Student";

SleepDeprivedStudent::SleepDeprivedStudent(QWidget* widget, QString name, int maxHp, double skillSpeed, int cost, int damage)
    : AttackStudent(widget, name, maxHp, skillSpeed, cost, damage)
{

}

void SleepDeprivedStudent::skill() {}

void SleepDeprivedStudent::update() {}
