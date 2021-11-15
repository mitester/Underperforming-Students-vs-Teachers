#ifndef TEACHER_H
#define TEACHER_H

#include "human.h"
#include "student.h"

/***
    Author: Tse Wai Chung
    Date: 11/13/2021
*/
class Teacher : public Human
{
    Q_OBJECT

public:
    /* Mutators */
    double getSpeed() const;
    void setSpeed(double speed);
    int getDamage() const;
    void setDamage(int damage);

    // the default attack behaviour of teacher
    virtual void attack(Student& s);
    virtual void update() = 0;

    TimeVariant::Category getCategory() const;

protected:
    explicit Teacher(QLabel *widget, QString name, int maxHp, double speed, int damage);
private:
    double speed;
    int damage;
};

#endif // TEACHER_H
