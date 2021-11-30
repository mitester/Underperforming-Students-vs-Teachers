#include "overworkedta.h"
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

const QString OverworkedTA::DEFAULT_NAME = "Overworked TA";

QPixmap* OverworkedTA::PIC_0 = nullptr;
QPixmap* OverworkedTA::PIC_1 = nullptr;
QPixmap* OverworkedTA::PIC_2 = nullptr;
QPixmap* OverworkedTA::PIC_3 = nullptr;

OverworkedTA::OverworkedTA(QLabel *widget, Row* row, QString name, int maxHp, int speed, int damage) :
    Teacher(widget, row, name, maxHp, speed, damage)
{

}

TimeVariant::Type OverworkedTA::getType() const {return TimeVariant::Type::OVERWORKED_TA;}

void OverworkedTA::update() {
    // initialization (get all the references)

    // Logic of OverworkedTA's update:
    //
    if(!widget->isEnabled())
        return ;

    // Self destruction (after reached the right end)
    if(this->getDistanceFromLeft() > Game::TEA_GEN_POS) {//when the teacher is outside of the leftmost distance.
        row->removeTeacher(this);
        return ;
    }

    // Explosion Animator
    if(deadCounter >= 1) { //enters the "explosion mode"
        //this->widget->setDisabled(true);
        if(counter % 10 == 0) {
            widget->setFixedSize(Teacher::SPRITE_HEIGHT, Teacher::SPRITE_HEIGHT);
            if(deadCounter == 1) {
                widget->setPixmap(*Item::EXPLOSION_0);
                player->setMedia(QUrl("qrc:/sounds/explosion.wav"));
                player->play();
            }
            if(deadCounter == 2)
                widget->setPixmap(*Item::EXPLOSION_1);
            if(deadCounter == 3)
                widget->setPixmap(*Item::EXPLOSION_2);
            if(deadCounter == 4)
                row->removeTeacher(this);
            deadCounter ++;
        }
        counter ++;
        return;
    }

    // Get all necessary information for the teacher to detect collision
    QRect shape = widget->geometry();
    const Teacher* leftTeacher = this->row->getLeftMostTeacher();
    const Assignment* rightAssignment = this->row->getRightMostAssignment();
    const Student* rightStudent = this->row->getRightMostStudent();


    // the teacher intersects with the leftmost teacher, update the left most teacher position
    if(this != leftTeacher && shape.intersects(leftTeacher->getWidget()->geometry()))
        row->updateLeftMostTeacher();


    // the teacher hits an assignment,
    if (rightAssignment && shape.intersects(rightAssignment->getWidget()->geometry())) {

        // reduce the teacher's hp
        this->hp -= rightAssignment->getDamage();
        if(this->hp <= 0)
            deadCounter++;  // if no more hp, enters the "explosion" animation

        // remove the assignment
        Assignment* preRemove = row->popRightMostAssignment();
        preRemove->deleteLater();
        widget->move(widget->x() - speed / 2, widget->y()); // speed reduced after being hit

        // play the sound effect of being hit
        player->play();
    }


    // the teacher hits a student
    if (rightStudent && shape.intersects(rightStudent->getWidget()->geometry())) {

        // if the student is Teacher's pet (we need to turn back)
        if(rightStudent->getType() == TimeVariant::Type::TEACHERS_PET) {
            speed = -speed;
            row->setRightMostStudentHp(0);
        } else  // otherwise just attack the student
            row->setRightMostStudentHp(rightStudent->getHp() - damage);

        // if the student has no hp after our attack, delete it
        if(rightStudent->getHp() <= 0) {
            Student* preRemove = row->popRightMostStudent();
            preRemove->deleteLater();
        }

    } else { // hit nothing, move forward.

        // The move animation setter
        if(counter % 3 == 0)  { // speed control
            widget->move(widget->x() - speed, widget->y());

            if(counter >= abs(speed) * 5) { // the speed is abs() because it may be negative (moving backward)
                if(speed > 0) { // moving in right direction, use the corresponding pixmap
                    if(firstLeg)
                        widget->setPixmap(*OverworkedTA::PIC_1);
                    else
                        widget->setPixmap(*OverworkedTA::PIC_0);
                } else {    // moving in reversed direction, use the reversed pixmap
                    if(firstLeg)
                        widget->setPixmap(*OverworkedTA::PIC_3);
                    else
                        widget->setPixmap(*OverworkedTA::PIC_2);
                }
                firstLeg = !firstLeg;   // change the leg after moving
                counter = 0;
            }
        }

    }

    counter ++;
}

