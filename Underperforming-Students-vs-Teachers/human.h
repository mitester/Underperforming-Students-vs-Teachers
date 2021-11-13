/*
* This is a superclass of Student and Teacher
*/
#ifndef HUMAN_H
#define HUMAN_H

#include <QString>
#include "timevariant.h"

/*changed this a little bit: public get/set Hp*/
class Human : public TimeVariant
{
public:
    //getter and setter for hp
    int getHp();
    void setHp(int hp);
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


};

#endif // HUMAN_H
