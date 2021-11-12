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
    SleepDeprivedStudent(QWidget* widget, QString name, int maxHp, double skillSpeed, int cost, int damage);

    //constructor for a Default SleepDeprivedStudent
    SleepDeprivedStudent(QWidget* widget);

    //the implementation of the pure virtual skill()
    void skill();

    //the implementation of the pure virtual update()
    void update();

};

#endif // SLEEPDEPRIVEDSTUDENT_H
