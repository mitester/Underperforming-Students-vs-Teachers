/***
* This is the student class
*/
#ifndef STUDENT_H
#define STUDENT_H

#include "human.h"

class Row;

class Student : public Human
{
    Q_OBJECT

public:
    //getter and setter for skillSpeed
    int getSkillSpeed() const;
    void setSkillSpeed(int skillSpeed);

    //getter and setter for skillSpeed
    int getCost() const;
    void setCost(int cost);

protected:
    //protected constructor
    Student(QLabel* widget, Row* row, QString name, int maxHp, int skillSpeed, int cost);

    //stores this student skillSpeed
    int skillSpeed;

    //stores this student deployment cost
    int cost;
};

#endif // STUDENT_H
