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

int Desmond::getSkillSpeed() const {    // accessor of skill speed
    return skillSpeed;
}

void Desmond::setSkillSpeed(int skillSpeed) {   // mutator of set skill speed
    this->skillSpeed = skillSpeed;
}

TimeVariant::Type Desmond::getType() const {return TimeVariant::Type::DESMOND;}

// A function that doubles the speed of all given teachers
// it is designed to be passed in as a function pointer to modifyTeachers();

void doubleSpeed(Teacher *t) {
    // note: the function is implemented in this way because originally there could be more than one desmond appear
    // together on the battlefield. (now there will be only one)
    // this approach can avoid more than one desmonds' skill effect over-strengthening the teachers
    // but this approach is more robust, so it is kept.
    int speed = 0;
    switch (t->getType()) { // set the speed according to the type of the teacher
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

// A function that halve the speed of all given teachers
// it is designed to be passed in as a function pointer to modifyTeachers();

void halveSpeed(Teacher *t) {
    // note: the function is implemented in this way because originally there could be more than one desmond appear
    // together on the battlefield. (now there will be only one)
    // this approach can avoid more than one desmonds' skill effect over-weakening the teachers
    // but this approach is more robust, so it is kept.
    int speed = 0;
    switch (t->getType()) { // set the speed according to the type of the teacher
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

    // remove the desmond after it reached the right end
    if(this->getDistanceFromLeft() > Game::TEA_GEN_POS) {//when the teacher is outside of the leftmost distance.
        row->removeTeacher(this);
        return ;
    }

    Game* game = Game::getInstance();

    // Explosion animator
    if(deadCounter >= 1) {  // the counter will count every 200 ms
        if(counter % 10 == 0) {     // to let the dead counter slow down 10 times: 20ms -> 200ms
            widget->setFixedSize(Teacher::SPRITE_HEIGHT, Teacher::SPRITE_HEIGHT);
            if(deadCounter == 1) {
                // the first deadcounter, set explosion image, play sound effect and cancel all the skill effects.
                player->setMedia(QUrl("qrc:/sounds/explosion.wav"));
                player->play();
                widget->setPixmap(*Item::EXPLOSION_0);
                if(speedIncreased) {
                    for(int i = 0; i < Game::NUMBER_OF_ROW; i++)
                        game->getRowAt(i)->modifyTeachers(halveSpeed);
                }
                game->desmond = nullptr;
            }
            if(deadCounter == 2)    // continue to set pixmap
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

    //get all information for collision
    QRect shape = widget->geometry();
    const Teacher* leftTeacher = this->row->getLeftMostTeacher();
    const Assignment* rightAssignment = this->row->getRightMostAssignment();
    const Student* rightStudent = this->row->getRightMostStudent();


    // desmond intersects with the leftmost teacher, update the teacher's leftmost position
    if(this != leftTeacher && shape.intersects(leftTeacher->getWidget()->geometry()))
        row->updateLeftMostTeacher();


    // desmond hits an assignment
    if (rightAssignment && shape.intersects(rightAssignment->getWidget()->geometry())) {

        // reduce desmond's hp
        this->hp -= rightAssignment->getDamage();
        if(this->hp <= 0)   // if no hp, explode
            deadCounter++;

        // remove the assignment
        Assignment* preRemove = row->popRightMostAssignment();
        preRemove->deleteLater();
        widget->move(widget->x() - speed / 2, widget->y()); // speed reduced after being hit

        player->play(); // play the sound effect of being hit

    }


    // desmond hits a student
    if (rightStudent && shape.intersects(rightStudent->getWidget()->geometry())) {

            // set the student's hp
            row->setRightMostStudentHp(rightStudent->getHp() - damage);

        if(rightStudent->getHp() <= 0) {    // if no hp, delete the student
            Student* preRemove = row->popRightMostStudent();
            preRemove->deleteLater();
        }


    } else { // hit nothing, move forward.

        if(counter % 4 == 0) {  // desmond's moving is slower
            widget->move(widget->x() - speed, widget->y());

            if(counter >= speed * 5) {  // he will only move in positive direction
                if(speed > 0) {
                    if(firstLeg)
                        widget->setPixmap(*Desmond::PIC_1);
                    else
                        widget->setPixmap(*Desmond::PIC_0);
                }
                firstLeg = !firstLeg;
                counter = 0;
            }
        }

    }

    // if the skill counter reached end
    if(counterSkill >= skillSpeed) {

        int k = QRandomGenerator::securelySeeded().bounded(0, 10);  // generate a random number

        if(k >= 4) { // "Do you want to learn more => increase speed"

            qDebug() << "Do you want to learn more?";
            widget->setPixmap(*Desmond::PIC_2); // change to desmond style
            for(int i = 0; i < Game::NUMBER_OF_ROW; i++)    // for every teacher, increase their speed
                game->getRowAt(i)->modifyTeachers(doubleSpeed);
            speedIncreased = true;  // there is speed increase effect

        } else {    // "additional class"

            qDebug() << "Let's have some additional class";
            game->addRedbull(-3);
            widget->setPixmap(*Desmond::PIC_3); // change to desmond style
            speedIncreased = true;

        }

        counterSkill = 0;
    }

    if(speedIncreased && countdown++ >= SPEED_INCREASE_COUNTDOWN) { // the cool down for speed increment effect
        countdown = 0;
        for(int i = 0; i < Game::NUMBER_OF_ROW; i++)    // when the skill ends, set their skill back to havlved stage.
            game->getRowAt(i)->modifyTeachers(halveSpeed);
    }

    counter ++;
    counterSkill++;
}
