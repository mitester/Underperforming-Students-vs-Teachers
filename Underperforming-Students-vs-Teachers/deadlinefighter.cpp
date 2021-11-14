#include "deadlinefighter.h"

const QString DeadlineFighter::DEFAULT_NAME = "Deadline Fighter";


DeadlineFighter::DeadlineFighter(QWidget* widget, QString name, int maxHp, double skillSpeed, int cost, int damage)
    : AttackStudent(widget, name, maxHp, skillSpeed, cost, damage)
{

}

void DeadlineFighter::skill() {}

void DeadlineFighter::update() {}
