#include "cgagod.h"

const QString CgaGod::DEFAULT_NAME = "CGA God";

QPixmap* CgaGod::PIC_0 = nullptr;
QPixmap* CgaGod::PIC_1 = nullptr;
QPixmap* CgaGod::PIC_2 = nullptr;


CgaGod::CgaGod(QLabel* widget, Row* row, QString name, int maxHp, int skillSpeed, int cost, int damage)
    : AttackStudent(widget, row, name, maxHp, skillSpeed, cost, damage)
{

}

TimeVariant::Type CgaGod::getType() const {return TimeVariant::Type::CGA_GOD;}

void CgaGod::update() {}
