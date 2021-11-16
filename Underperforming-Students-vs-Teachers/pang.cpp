#include "pang.h"

const QString Pang::DEFAULT_NAME = "Pang";


Pang::Pang(QLabel *widget, QString name, int maxHp, double speed, int damage) :
    Teacher(widget, name, maxHp, speed, damage)
{

}

TimeVariant::Type Pang::getType() const {return TimeVariant::Type::PANG;}

void Pang::update() {

}
