#include "desmond.h"

Desmond::Desmond(QWidget *widget, QString name, int maxHp, double speed, int damage, double skillSpeed) :
    Teacher(widget, name, maxHp, speed, damage), skillSpeed(skillSpeed)
{

}

double Desmond::getSkillSpeed() const {
    return skillSpeed;
}

void Desmond::setSkillSpeed(double skillSpeed) {
    this->skillSpeed = skillSpeed;
}

void Desmond::skill() {

}

void Desmond::update() {

}
