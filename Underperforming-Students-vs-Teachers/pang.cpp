#include "pang.h"
#include "teacher.h"
#include "human.h"
#include <algorithm>
#include <queue>
#include "row.h"
#include "timevariant.h"
#include "human.h"
#include "assignment.h"
#include "item.h"
#include "kelvin.h"
#include <QLabel>

const QString Pang::DEFAULT_NAME = "Pang";

QPixmap* Pang::PIC_0 = nullptr;
QPixmap* Pang::PIC_1 = nullptr;
QPixmap* Pang::PIC_2 = nullptr;
QPixmap* Pang::PIC_3 = nullptr;

Pang::Pang(QLabel *widget, Row* row,QString name, int maxHp, int speed, int damage) :
    Teacher(widget, row, name, maxHp, speed, damage)
{

}

TimeVariant::Type Pang::getType() const {return TimeVariant::Type::PANG;}

void Pang::update() {
    // initialization (get all the references)
    if(!widget->isEnabled())
        return ;

    if(this->getDistanceFromLeft() > Game::TEA_GEN_POS) {
        row->removeTeacher(this);
        return ;
    }

    QRect shape = widget->geometry();
    const Teacher* leftTeacher = this->row->getLeftMostTeacher();
    const Assignment* rightAssignment = this->row->getRightMostAssignment();
    const Student* rightStudent = this->row->getRightMostStudent();

    if(this != leftTeacher && shape.intersects(leftTeacher->getWidget()->geometry())) { // a teacher intersects with the leftmost teacher

        row->updateLeftMostTeacher();

    }

    if (rightAssignment && shape.intersects(rightAssignment->getWidget()->geometry())) { // hit an assignment

        this->hp -= rightAssignment->getDamage();
        if(this->hp <= 0)
            row->removeTeacher(this);

        Assignment* preRemove = row->popRightMostAssignment();
        preRemove->deleteLater();
        widget->move(widget->x() - speed / 2, widget->y()); // speed reduced after being hit

    }

    if (rightStudent && shape.intersects(rightStudent->getWidget()->geometry())) {   // hit a student

        if(rightStudent->getType() == TimeVariant::Type::TEACHERS_PET) {
            speed = -speed;
            row->setRightMostStudentHp(0);
        } else
            row->setRightMostStudentHp(rightStudent->getHp() - damage);

        if(rightStudent->getHp() <= 0) {
            Student* preRemove = row->popRightMostStudent();
            preRemove->deleteLater();
        }

    } else { // hit nothing, move forward.

        if(counter % 3 == 0) {
            widget->move(widget->x() - speed, widget->y());

            if(counter >= abs(speed) * 2) {
                if(speed > 0) {
                    if(firstLeg)
                        widget->setPixmap(*Pang::PIC_1);
                    else
                        widget->setPixmap(*Pang::PIC_0);
                } else {
                    if(firstLeg)
                        widget->setPixmap(*Pang::PIC_3);
                    else
                        widget->setPixmap(*Pang::PIC_2);
                }
                firstLeg = !firstLeg;
                counter = 0;
            }
        }

    }

    counter ++;
}
