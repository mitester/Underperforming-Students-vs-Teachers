/***
* This is the student class
*/
#ifndef STUDENT_H
#define STUDENT_H

#include "human.h"

class Student : public Human
{
    Q_OBJECT

public:
    //getter and setter for skillSpeed
    double getSkillSpeed() const;
    void setSkillSpeed(double skillSpeed);

    //getter and setter for skillSpeed
    int getCost() const;
    void setCost(int cost);

protected:
    //protected constructor
    Student(QLabel* widget, QString name, int maxHp, double skillSpeed, int cost);

    //stores this student skillSpeed
    double skillSpeed;

    //stores this student deployment cost
    int cost;
};

#endif // STUDENT_H
