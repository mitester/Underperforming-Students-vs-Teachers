/*
* This is the student class
*/
#ifndef STUDENT_H
#define STUDENT_H

#include "human.h"

class Student : public Human
{
protected:
    //protected constructor
    Student(QWidget* widget, QString name, int maxHp, double skillSpeed, int cost);

    //stores this student skillSpeed
    double skillSpeed;

    //stores this student deployment cost
    int cost;

    //getter and setter for skillSpeed
    double getSkillSpeed();
    void setSkillSpeed(double skillSpeed);

    //getter and setter for skillSpeed
    int getCost();
    void setCost(int cost);

    //restrict all subclasses to provide a skill implementation
    virtual void skill() = 0;
};

#endif // STUDENT_H
