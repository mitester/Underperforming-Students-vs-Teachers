#include "assignment.h"
#include <QDebug>
#include "game.h"
#include "row.h"

Assignment::Assignment(QLabel* widget, Row* row, int damage, int speed) : Item(widget, row), damage(damage), speed(speed)
{
}

void Assignment::update()
{
    if(widget->x() >= Game::TEA_GEN_POS)
    {
        row->popRightMostAssignment();
        deleteLater();
    }
    widget->move(widget->x() + speed, widget->y());
}

TimeVariant::Type Assignment::getType() const
{
    return TimeVariant::Type::ASSIGNMENT;
}

int Assignment::getDamage() const
{
    return this->damage;
}
