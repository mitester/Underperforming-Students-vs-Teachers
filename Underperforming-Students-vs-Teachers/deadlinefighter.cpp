#include "deadlinefighter.h"

const QString DeadlineFighter::DEFAULT_NAME = "Deadline Fighter";


DeadlineFighter::DeadlineFighter(QLabel* widget, QString name, int maxHp, double skillSpeed, int cost, int damage)
    : AttackStudent(widget, name, maxHp, skillSpeed, cost, damage)
{

}

TimeVariant::Type DeadlineFighter::getType() const {return TimeVariant::Type::DEADLINE_STUDENT;}

void DeadlineFighter::update() {}
