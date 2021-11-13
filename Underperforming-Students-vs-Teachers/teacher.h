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
public:
    /* Mutators */
    double getSpeed() const;
    void setSpeed(double speed);
    int getAtk() const;
    void setAtk(int atk);

    // the default attack behaviour of teacher
    virtual void attack(Student& s);
    virtual void update() = 0;

protected:
    explicit Teacher(QWidget *widget, QString name, int maxHp, double speed, int atk);
private:
    double speed;
    int atk;
};

#endif // TEACHER_H
