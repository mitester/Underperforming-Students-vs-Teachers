#include "teacher.h"
#include <algorithm>

Teacher::Teacher(QWidget *widget, QString name, int maxHp, double speed, int damage) :
    Human(widget, name, maxHp), speed(speed), damage(damage)
{

}

int Teacher::getDamage() const {
    return damage;
}

void Teacher::setDamage(int damage) {
    this->damage = damage;
}

double Teacher::getSpeed() const {
    return speed;
}

void Teacher::setSpeed(double speed) {
    this->speed = speed;
}

//TODO
void Teacher::attack(Student& s) {
    int hp = s.getHp();
    if(hp >= 0) {
        s.setHp(std::max(0, hp - damage)); // if damage is more than the student's current hp, simply set it to 0
    }
}

