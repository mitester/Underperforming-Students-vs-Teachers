/*
* This is the student class
*/
#ifndef STUDENT_H
#define STUDENT_H

#include "human.h"

class Student : public Human
{
public:
    //restrict all subclasses to provide a deployment cost
    virtual int getCost() = 0;

    //restrict all subclasses to provide a skill speed
    virtual double getSkillSpeed() = 0;

    //restrict all subclasses to provide a skill implementation
    virtual void skill() = 0;

protected:
    //protected constructor
    Student();
};

#endif // STUDENT_H
