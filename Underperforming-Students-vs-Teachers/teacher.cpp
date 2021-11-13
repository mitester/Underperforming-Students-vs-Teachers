#include "teacher.h"
#include <algorithm>

Teacher::Teacher(QWidget *widget, QString name, int maxHp, double speed, int attack) :
    Human(widget, name, maxHp), speed(speed), atk(attack)
{

}

int Teacher::getAtk() const {
    return atk;
}

void Teacher::setAtk(int atk) {
    this->atk = atk;
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
        s.setHp(std::max(0, hp - atk)); // if atk is more than the student's current hp, simply set it to 0
    }
}

