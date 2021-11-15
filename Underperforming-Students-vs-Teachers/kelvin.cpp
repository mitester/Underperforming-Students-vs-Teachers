#include "kelvin.h"

Kelvin::Kelvin(QLabel *widget, QString name, int maxHp, double speed, int damage) :
    Teacher(widget, name, maxHp, speed, damage)
{

}

TimeVariant::Type Kelvin::getType() const {return TimeVariant::Type::KELVIN;}

void Kelvin::update() {

}
