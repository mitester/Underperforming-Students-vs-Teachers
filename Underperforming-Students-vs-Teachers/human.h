/***
* This is a superclass of Student and Teacher
*/
#ifndef HUMAN_H
#define HUMAN_H

#include <QString>
#include "timevariant.h"

class Row;

class Human : public TimeVariant
{
    Q_OBJECT

public:
    static const int SPRITE_WDITH{100};
    static const int SPRITE_HEIGHT{130};

    //getter and setter for name
    QString getName() const;
    void setName(QString name);

    //getter and setter for maxHp
    int getMaxHp() const;
    void setMaxHp(int maxHp);

    //getter and setter for hp
    int getHp() const;
    void setHp(int hp);

    Row* getRow();

protected:
    //protected constructor, nobody could create a human instance except children
    Human(QLabel *widget, Row* row, QString name, int maxHp);

    QString name;

    int hp;

    int maxHp;
};

#endif // HUMAN_H
