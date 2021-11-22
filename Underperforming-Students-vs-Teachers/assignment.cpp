#include "assignment.h"
#include <QDebug>
#include "game.h"

Assignment::Assignment(QLabel* widget, Row* row, int damage, int speed) : Item(widget, row), damage(damage), speed(speed)
{
}

void Assignment::update()
{
    widget->move(widget->x() + 3, widget->y());
}

TimeVariant::Type Assignment::getType() const
{
    return TimeVariant::Type::ASSIGNMENT;
}

int Assignment::getDamage() const
{
    return this->damage;
}
