#include "desmond.h"

Desmond::Desmond(QLabel *widget, QString name, int maxHp, double speed, int damage, double skillSpeed) :
    Teacher(widget, name, maxHp, speed, damage), skillSpeed(skillSpeed)
{

}

double Desmond::getSkillSpeed() const {
    return skillSpeed;
}

void Desmond::setSkillSpeed(double skillSpeed) {
    this->skillSpeed = skillSpeed;
}

TimeVariant::Type Desmond::getType() const {return TimeVariant::Type::DESMOND;}

void Desmond::skill() {

}

void Desmond::update() {

}
