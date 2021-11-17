#include "cgagod.h"

const QString CgaGod::DEFAULT_NAME = "CGA God";


CgaGod::CgaGod(QLabel* widget, Row* row, QString name, int maxHp, double skillSpeed, int cost, int damage)
    : AttackStudent(widget, row, name, maxHp, skillSpeed, cost, damage)
{

}

TimeVariant::Type CgaGod::getType() const {return TimeVariant::Type::CGA_GOD;}

void CgaGod::update() {}
