#ifndef TEACHER_H
#define TEACHER_H

#include "human.h"
#include "student.h"


/***
    Author: Tse Wai Chung
    Date: 11/13/2021
*/

class Row;

class Teacher : public Human
{
    Q_OBJECT

public:
    static const int SPRITE_WIDTH{62};
    static const int SPRITE_HEIGHT{125};

    /* Mutators */
    int getSpeed() const;
    void setSpeed(int speed);
    int getDamage() const;
    void setDamage(int damage);

    // the default attack behaviour of teacher
    virtual void attack(Student& s);
    virtual void update();

    TimeVariant::Category getCategory() const;

protected:
    explicit Teacher(QLabel *widget, Row* row, QString name, int maxHp, int speed, int damage);
private:
    int speed;
    int damage;
};

#endif // TEACHER_H
