#include "attackstudent.h"

AttackStudent::AttackStudent(QWidget* widget, QString name, int maxHp, double skillSpeed, int cost, int damage)
    : Student (widget, name, maxHp, skillSpeed, cost), damage(damage)
{
}

int AttackStudent::getDamage() {return damage;}

void AttackStudent::setDamage(int damage) {this->damage = damage;}
