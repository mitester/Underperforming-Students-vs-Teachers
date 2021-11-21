#include "assignment.h"
#include <QDebug>
#include "game.h"

Assignment::Assignment(QLabel* widget, Row* row, int damage, int assignmentX, int assignmentY) : Item(widget, row), damage(damage)
{
    widget->hide();
    widget->setPixmap(QPixmap(":/images/items/item_assignment_0.png"));
    widget->setFixedSize(spriteWidth, spriteHeight);
    widget->move(assignmentX, assignmentY);
    widget->show();
}

void Assignment::update()
{
    widget->move(widget->x() + 3, widget->y());
}

TimeVariant::Type Assignment::getType() const
{
    return TimeVariant::Type::ASSIGNMENT;
}
