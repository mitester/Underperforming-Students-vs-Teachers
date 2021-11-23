#include "desmond.h"

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

void Desmond::update() {

}
