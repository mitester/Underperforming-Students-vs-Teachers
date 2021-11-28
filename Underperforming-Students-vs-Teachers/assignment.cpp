#include "assignment.h"
#include <QDebug>
#include "game.h"
#include "row.h"

QPixmap* Assignment::PIC_0 = nullptr;
QPixmap* Assignment::PIC_1 = nullptr;
QPixmap* Assignment::PIC_2 = nullptr;

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
