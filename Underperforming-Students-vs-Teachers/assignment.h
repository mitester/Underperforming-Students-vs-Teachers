#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include "item.h"

class Assignment : public Item
{
    Q_OBJECT
public:
    static const int SPRITE_WIDTH{45};
    static const int SPRITE_HEIGHT{37};

    Assignment(QLabel* widget, Row* row, int damage);

    void update(); //implement update() from TimeVariant

    TimeVariant::Type getType() const;

    int getDamage() const;

private:
    int damage = 0;
};

#endif // ASSIGNMENT_H
