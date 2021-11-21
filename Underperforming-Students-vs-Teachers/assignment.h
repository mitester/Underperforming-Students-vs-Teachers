#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include "item.h"

class Assignment : public Item
{
    Q_OBJECT
public:
    static const int spriteWidth{45};
    static const int spriteHeight{37};

    Assignment(QLabel* widget, Row* row, int damage, int assignmentX, int assignmentY);

    void update(); //implement update() from TimeVariant

    TimeVariant::Type getType() const;

private:
    int damage = 0;
};

#endif // ASSIGNMENT_H
