/*
* This is a superclass of Student and Teacher
*/
#ifndef HUMAN_H
#define HUMAN_H

#include <QString>
#include "timevariant.h"

class Human : public TimeVariant
{
public:
    //restrict all subclasses to provide a name
    virtual QString getName() = 0;

    //restrict all subclasses to provide a max hp
    virtual int getMaxHp() = 0;

    //getter and setter for hp
    int getHp();
    void setHp(int hp);

protected:
    //protected constructor, nobody could create a human instance except children
    Human();

private:
    int hp;
};

#endif // HUMAN_H
