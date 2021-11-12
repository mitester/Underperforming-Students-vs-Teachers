/*
* This is a class of Attack Student
* It can be instantiated
*/
#ifndef SLEEPDEPRIVEDSTUDENT_H
#define SLEEPDEPRIVEDSTUDENT_H

#include "attackstudent.h"

class SleepDeprivedStudent : public AttackStudent
{
public:
    static const QString defaultName;
    static const int defaultMaxHp{10};
    static constexpr double defaultSkillSpeed{10.0}; //compiler said it should be constexpr for static double
    static const int defaultCost{10};
    static const int defaultDamage{10};

    SleepDeprivedStudent(QWidget* widget,
                         QString name = defaultName,
                         int maxHp = defaultMaxHp,
                         double skillSpeed = defaultSkillSpeed,
                         int cost = defaultCost,
                         int damage = defaultDamage);

    //the implementation of the pure virtual skill()
    void skill();

    //the implementation of the pure virtual update()
    void update();

};

#endif // SLEEPDEPRIVEDSTUDENT_H
