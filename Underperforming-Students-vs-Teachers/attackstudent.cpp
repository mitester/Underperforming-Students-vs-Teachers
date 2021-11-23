#include "attackstudent.h"

AttackStudent::AttackStudent(QLabel* widget, Row* row, QString name, int maxHp, int skillSpeed, int cost, int damage)
    : Student (widget, row, name, maxHp, skillSpeed, cost), damage(damage)
{
}

int AttackStudent::getDamage() const {return damage;}

void AttackStudent::setDamage(int damage) {this->damage = damage;}

TimeVariant::Category AttackStudent::getCategory() const {return TimeVariant::Category::ATTACK_STUDENT;}
