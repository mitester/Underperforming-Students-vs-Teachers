/*
* This is a superclass of Student and Teacher
*/
#ifndef HUMAN_H
#define HUMAN_H

#include <QString>
#include "timevariant.h"

class Human : public TimeVariant
{
protected:
    //protected constructor, nobody could create a human instance except children
    Human(QWidget *widget, QString name, int maxHp);

    QWidget *widget;

    QString name;

    int hp;

    int maxHp;

    //getter and setter for w
    QWidget getWidget();
    void setWidget(QWidget* widget);

    //getter and setter for name
    QString getName();
    int setName(QString name);

    //getter and setter for maxHp
    int getMaxHp();
    void setMaxHp(int maxHp);

    //getter and setter for hp
    int getHp();
    void setHp(int hp);
};

#endif // HUMAN_H