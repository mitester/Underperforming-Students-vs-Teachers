#include "attackstudent.h"

AttackStudent::AttackStudent(QLabel* widget, QString name, int maxHp, double skillSpeed, int cost, int damage)
    : Student (widget, name, maxHp, skillSpeed, cost), damage(damage)
{
}

int AttackStudent::getDamage() const {return damage;}

void AttackStudent::setDamage(int damage) {this->damage = damage;}

TimeVariant::Category AttackStudent::getCategory() const {return TimeVariant::Category::ATTACK_STUDENT;}
