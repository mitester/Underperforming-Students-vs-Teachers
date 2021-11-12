#include "sleepdeprivedstudent.h"
#include "GameLiterals.h"

SleepDeprivedStudent::SleepDeprivedStudent(QWidget* widget, QString name, int maxHp, double skillSpeed, int cost, int damage)
    : AttackStudent(widget, name, maxHp, skillSpeed, cost, damage)
{

}

SleepDeprivedStudent::SleepDeprivedStudent(QWidget *widget)
    : AttackStudent(widget,
                    sleepDeprivedStudentDefaultName,
                    sleepDeprivedStudentDefaultMaxHp,
                    sleepDeprivedStudentDefaultSkillSpeed,
                    sleepDeprivedStudentDefaultCost,
                    sleepDeprivedStudentDefaultDamage)
{

}

void SleepDeprivedStudent::skill() {}

void SleepDeprivedStudent::update() {}
