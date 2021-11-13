/*
* This is the superclass of all students which attack
*/
#ifndef ATTACKSTUDENT_H
#define ATTACKSTUDENT_H

#include "student.h"

class AttackStudent : public Student
{
protected:
    AttackStudent(QWidget* widget, QString name, int maxHp, double skillSpeed, int cost, int damage);

    //the number of damage the Attack Student can make
    //It may change due to its skill
    int damage;

    //getter and setter for damage
    int getDamage() const;
    void setDamage(int damage);
};

#endif // ATTACKSTUDENT_H
