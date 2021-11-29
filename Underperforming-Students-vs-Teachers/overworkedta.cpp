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
    if(!widget->isEnabled())
        return ;

    if(this->getDistanceFromLeft() > Game::TEA_GEN_POS) {   //when the teacher is outside of the leftmost distance.
        row->removeTeacher(this);
        return ;
    }

    if(deadCounter >= 1) { //enters the "explosion mode"
        //this->widget->setDisabled(true);
        if(counter % 10 == 0) {
            widget->setFixedSize(Teacher::SPRITE_HEIGHT, Teacher::SPRITE_HEIGHT);
            if(deadCounter == 1) {
                player->setMedia(QUrl("qrc:/sounds/explosion.wav"));
                player->play();
                widget->setPixmap(*Item::EXPLOSION_0);
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
            deadCounter++;

        Assignment* preRemove = row->popRightMostAssignment();
        preRemove->deleteLater();
        widget->move(widget->x() - speed / 2, widget->y()); // speed reduced after being hit

        //player->setMedia(QUrl("qrc:/sounds/hit.wav"));
        //player->play();

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

            if(counter >= abs(speed) * 5) {
                if(speed > 0) {
                    if(firstLeg)
                        widget->setPixmap(*OverworkedTA::PIC_1);
                    else
                        widget->setPixmap(*OverworkedTA::PIC_0);
                } else {
                    if(firstLeg)
                        widget->setPixmap(*OverworkedTA::PIC_3);
                    else
                        widget->setPixmap(*OverworkedTA::PIC_2);
                }
                firstLeg = !firstLeg;
                counter = 0;
            }
        }

    }

    counter ++;
}

