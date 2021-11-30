/***
 * Assignment implementation
 */
#include "assignment.h"
#include <QDebug>
#include "game.h"
#include "row.h"

//setting default values of Assignment pictures
QPixmap* Assignment::PIC_0 = nullptr;
QPixmap* Assignment::PIC_1 = nullptr;
QPixmap* Assignment::PIC_2 = nullptr;

Assignment::Assignment(QLabel* widget, Row* row, int damage, int speed) : Item(widget, row), damage(damage), speed(speed)
{
}

// implement the update() from TimeVariant
// it is called per BASIC_TIME_UNIT
void Assignment::update()
{
    // if it arrive the teacher generating position
    // means it doesn't hit any teacher
    // so pop it out from the container in row and delete it by deleteLater()
    if(widget->x() >= Game::TEA_GEN_POS)
    {
        row->popRightMostAssignment();
        deleteLater();
        return;
    }

    // else move the assignment forward with speed
    widget->move(widget->x() + speed, widget->y());
}

// it returns the type of Assignment
TimeVariant::Type Assignment::getType() const
{
    return TimeVariant::Type::ASSIGNMENT;
}

//getter of damage
int Assignment::getDamage() const
{
    return this->damage;
}
