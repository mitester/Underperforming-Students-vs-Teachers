#include "teacher.h"
#include "human.h"
#include <algorithm>
#include <queue>
#include "row.h"
#include "timevariant.h"
#include "human.h"
#include "assignment.h"
#include "item.h"

Teacher::Teacher(QLabel *widget, Row* row, QString name, int maxHp, int speed, int damage) :
    Human(widget, row, name, maxHp), speed(speed), damage(damage)
{

}

TimeVariant::Category Teacher::getCategory() const {return TimeVariant::Category::TEACHER;}

int Teacher::getDamage() const {
    return damage;
}

void Teacher::setDamage(int damage) {
    this->damage = damage;
}

int Teacher::getSpeed() const {
    return speed;
}

void Teacher::setSpeed(int speed) {
    this->speed = speed;
}

//TODO
void Teacher::attack(Student& s) {

}

void Teacher::update() {
    // initialization (get all the references)
    QRect shape = widget->geometry();
    const Teacher* leftTeacher = this->row->getLeftMostTeacher();
    const Assignment* rightAssignment = this->row->getRightMostAssignment();
    const Student* rightStudent = this->row->getRightMostStudent();

    //
    if(this != leftTeacher && shape.intersects(leftTeacher->getWidget()->geometry())) { // a teacher intersects with the leftmost teacher

        row->updateLeftMostTeacher();

    } else if (shape.intersects(rightAssignment->getWidget()->geometry())) { // hit an assignment

        this->hp -= rightAssignment->getDamage();
        if(this->hp <= 0) {
            this->widget->setEnabled(false);
            this->widget->hide();
        }
        row->popRightMostAssignment();
        rightAssignment->getWidget()->setEnabled(false);
        rightAssignment->getWidget()->hide();

        widget->move(widget->x() + speed / 2, widget->y()); // speed reduced after being hit

    } else if (shape.intersects(rightStudent->getWidget()->geometry())) {   // hit a student

        row->setRightMostStudentHp(rightStudent->getHp() - damage);
        if(rightStudent->getHp() <= 0) {
            row->popRightMostStudent();
            rightStudent->getWidget()->setEnabled(false);
            rightStudent->getWidget()->hide();
        }

    } else { // hit nothing, move forward.

        widget->move(widget->x() + speed, widget->y());

    }


}

