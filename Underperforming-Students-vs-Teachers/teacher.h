#ifndef TEACHER_H
#define TEACHER_H

#include "human.h"
#include "student.h"


/***
 *   Date: 11/13/2021
 *
 *   The class of Teacher.
 *
 *   All teachers has speed (they can move) and damage (attack).
 *   They are of the same height and width.
 *
 *   So, this class provides accessors and mutators for speed and damage for any teachers.
 *   Some protected counters are also added for animations and sound effects
 *

*/

class Row;

class Teacher : public Human
{
    Q_OBJECT

public:
    static const int SPRITE_WIDTH{110};
    static const int SPRITE_HEIGHT{163};

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
    int speed;
    int damage;
    int counter = 0;
    int deadCounter = 0;
    bool firstLeg = true;
private:

};

#endif // TEACHER_H
