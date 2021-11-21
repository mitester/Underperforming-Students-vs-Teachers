#include "deadlinefighter.h"

const QString DeadlineFighter::DEFAULT_NAME = "Deadline Fighter";


DeadlineFighter::DeadlineFighter(QLabel* widget, Row* row, QString name, int maxHp, int skillSpeed, int cost, int damage)
    : AttackStudent(widget, row, name, maxHp, skillSpeed, cost, damage)
{

}

TimeVariant::Type DeadlineFighter::getType() const {return TimeVariant::Type::DEADLINE_STUDENT;}

void DeadlineFighter::update() {}
