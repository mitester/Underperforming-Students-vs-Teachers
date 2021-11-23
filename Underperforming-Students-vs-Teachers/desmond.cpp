#include "desmond.h"

const QString Desmond::DEFAULT_NAME = "Desmond";

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

void Desmond::update() {

}
