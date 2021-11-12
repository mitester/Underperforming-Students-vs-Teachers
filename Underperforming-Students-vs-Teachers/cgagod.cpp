#include "cgagod.h"

const QString CgaGod::defaultName = "CGA God";


CgaGod::CgaGod(QWidget* widget, QString name, int maxHp, double skillSpeed, int cost, int damage)
    : AttackStudent(widget, name, maxHp, skillSpeed, cost, damage)
{

}

void CgaGod::skill() {}

void CgaGod::update() {}
