#include "teacher.h"
#include "human.h"
#include <algorithm>
#include <queue>

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

