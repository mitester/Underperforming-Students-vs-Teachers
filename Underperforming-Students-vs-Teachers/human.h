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
    //getter and setter for name
    QString getName() const;
    void setName(QString name);

    //getter and setter for maxHp
    int getMaxHp() const;
    void setMaxHp(int maxHp);

    //getter and setter for hp
    int getHp() const;
    void setHp(int hp);

protected:
    //protected constructor, nobody could create a human instance except children
    Human(QWidget *widget, QString name, int maxHp);

    QString name;

    int hp;

    int maxHp;
};

#endif // HUMAN_H
