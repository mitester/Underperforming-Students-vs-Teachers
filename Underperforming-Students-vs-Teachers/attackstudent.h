/***
* This is the superclass of all students which attack
*/
#ifndef ATTACKSTUDENT_H
#define ATTACKSTUDENT_H

#include "student.h"

class AttackStudent : public Student
{
    Q_OBJECT

public:
    //getter and setter for damage
    int getDamage() const;
    void setDamage(int damage);

    TimeVariant::Category getCategory() const;

protected:
    AttackStudent(QLabel* widget, Row* row, QString name, int maxHp, int skillSpeed, int cost, int damage);

    //the number of damage the Attack Student can make
    //It may change due to its skill
    int damage;

};

#endif // ATTACKSTUDENT_H
