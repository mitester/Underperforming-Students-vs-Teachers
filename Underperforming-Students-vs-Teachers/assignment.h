#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include "item.h"

class Assignment : public Item
{
    Q_OBJECT
public:
    static const int SPRITE_WIDTH{45};
    static const int SPRITE_HEIGHT{37};
    static const int DEFAULT_DAMAGE{0};
    static const int DEFAULT_SPEED{3};

    static QPixmap* PIC_0;

    Assignment(QLabel* widget, Row* row, int damage = DEFAULT_DAMAGE, int speed = DEFAULT_SPEED);

    void update(); //implement update() from TimeVariant

    TimeVariant::Type getType() const;

    int getDamage() const;

private:
    int damage;
    int speed;
};

#endif // ASSIGNMENT_H
