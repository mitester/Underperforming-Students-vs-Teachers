#include "desmond.h"
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
#include "pang.h"
#include "overworkedta.h"
#include <QRandomGenerator>
#include <QDebug>

const QString Desmond::DEFAULT_NAME = "Desmond";

QPixmap* Desmond::PIC_0 = nullptr;
QPixmap* Desmond::PIC_1 = nullptr;
QPixmap* Desmond::PIC_2 = nullptr;
QPixmap* Desmond::PIC_3 = nullptr;

Desmond::Desmond(QLabel *widget, Row* row, QString name, int maxHp, int speed, int damage, int skillSpeed) :
    Teacher(widget, row, name, maxHp, speed, damage), skillSpeed(skillSpeed)
{

}

int Desmond::getSkillSpeed() const {
    return skillSpeed;
}

void Desmond::setSkillSpeed(int skillSpeed) {
    this->skillSpeed = skillSpeed;
}

TimeVariant::Type Desmond::getType() const {return TimeVariant::Type::DESMOND;}

void Desmond::skill() {

}

void doubleSpeed(Teacher *t) {
    int speed = 0;
    switch (t->getType()) {
    case TimeVariant::Type::KELVIN:
        speed = Kelvin::DEFAULT_SPEED; break;
    case TimeVariant::Type::PANG:
        speed = Pang::DEFAULT_SPEED; break;
    case TimeVariant::Type::OVERWORKED_TA:
        speed = OverworkedTA::DEFAULT_SPEED; break;
    case TimeVariant::Type::DESMOND:
        speed = Desmond::DEFAULT_SPEED; break;
    default:
        return;
    }
    t->setSpeed(speed * 2);
    if(t->getType() == TimeVariant::Type::DESMOND)
        t->setSpeed(speed / 2);
    t->getWidget()->setStyleSheet("background-color: rgba(14, 249, 25, 0.21)");
}

void halveSpeed(Teacher *t) {
    int speed = 0;
    switch (t->getType()) {
    case TimeVariant::Type::KELVIN:
        speed = Kelvin::DEFAULT_SPEED; break;
    case TimeVariant::Type::PANG:
        speed = Pang::DEFAULT_SPEED; break;
    case TimeVariant::Type::OVERWORKED_TA:
        speed = OverworkedTA::DEFAULT_SPEED; break;
    case TimeVariant::Type::DESMOND:
        speed = Desmond::DEFAULT_SPEED; break;
    default:
        return;
    }
    t->setSpeed(speed);
    t->getWidget()->setStyleSheet(" ;");
}


void Desmond::update() {
    // initialization (get all the references)
    if(!widget->isEnabled())
        return ;

    if(this->getDistanceFromLeft() > Game::TEA_GEN_POS) {
        row->removeTeacher(this);
        return ;
    }

    if(deadCounter >= 1) { //enters the "explosion mode"
        //this->widget->setDisabled(true);
        if(counter % 10 == 0) {
            widget->setFixedSize(Teacher::SPRITE_HEIGHT, Teacher::SPRITE_HEIGHT);
            if(deadCounter == 1)
                widget->setPixmap(*Item::EXPLOSION_0);
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

    }

    if (rightStudent && shape.intersects(rightStudent->getWidget()->geometry())) {   // hit a student

//        if(rightStudent->getType() == TimeVariant::Type::TEACHERS_PET) {
//            speed = -speed;
//            row->setRightMostStudentHp(0);
//        } else
            row->setRightMostStudentHp(rightStudent->getHp() - damage);

        if(rightStudent->getHp() <= 0) {
            Student* preRemove = row->popRightMostStudent();
            preRemove->deleteLater();
        }


    } else { // hit nothing, move forward.

        if(counter % 4 == 0) {
            widget->move(widget->x() - speed, widget->y());

            if(counter >= speed * 5) {
                if(speed > 0) {
                    if(firstLeg)
                        widget->setPixmap(*Desmond::PIC_1);
                    else
                        widget->setPixmap(*Desmond::PIC_0);
                } else {
                    //if(firstLeg)
                        //widget->setPixmap(*Desmond::PIC_3); Recover after PIC3, PIC2 are added.
                    //else
                        //widget->setPixmap(*Desmond::PIC_2);
                }
                firstLeg = !firstLeg;
                counter = 0;
            }
        }

    }

    Game* game = Game::getInstance();
    if(counterSkill >= skillSpeed) {

        int k = QRandomGenerator::securelySeeded().bounded(0, 10);

        if(k >= 4) { // "Do you want to learn more => increase speed"

            qDebug() << "Do you want to learn more?";

            widget->setPixmap(*Desmond::PIC_2);

            for(int i = 0; i < Game::NUMBER_OF_ROW; i++)
                game->getRowAt(i)->modifyTeachers(doubleSpeed);

            speedIncreased = true;

        } else {    // "additional class"

            qDebug() << "Let's have some additional class";

            game->addRedbull(-3);

            widget->setPixmap(*Desmond::PIC_3);

            speedIncreased = true;

        }

        counterSkill = 0;
    }

    if(speedIncreased && countdown++ >= SPEED_INCREASE_COUNTDOWN) {
        countdown = 0;
        for(int i = 0; i < Game::NUMBER_OF_ROW; i++)
            game->getRowAt(i)->modifyTeachers(halveSpeed);
    }

    counter ++;
    counterSkill++;
}
