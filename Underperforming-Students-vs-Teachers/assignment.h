/***
* This class defines the behavior of Assignment
* it inherits from
*/
#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include "item.h"

class Assignment : public Item
{
    Q_OBJECT
public:
    //some constant defines the properties of an assignment
    static const int SPRITE_WIDTH{45};
    static const int SPRITE_HEIGHT{37};
    static const int DEFAULT_DAMAGE{0};
    static const int DEFAULT_SPEED{3};

    //sprite pictures for assignment
    //preloaded in GameWindow
    static QPixmap* PIC_0;
    static QPixmap* PIC_1;
    static QPixmap* PIC_2;

    //constructor
    Assignment(QLabel* widget, Row* row, int damage = DEFAULT_DAMAGE, int speed = DEFAULT_SPEED);

    void update(); //implement update() from TimeVariant

    //implemented getType() from getType()
    TimeVariant::Type getType() const;

    //get how many damage it does to teacher
    int getDamage() const;

private:
    int damage;
    int speed;
};

#endif // ASSIGNMENT_H
