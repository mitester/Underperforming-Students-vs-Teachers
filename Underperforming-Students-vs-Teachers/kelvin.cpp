#include "kelvin.h"

const QString Kelvin::DEFAULT_NAME = "Kelvin";

QPixmap* Kelvin::PIC_0 = nullptr;
QPixmap* Kelvin::PIC_1 = nullptr;

Kelvin::Kelvin(QLabel *widget, Row* row, QString name, int maxHp, int speed, int damage) :
    Teacher(widget, row, name, maxHp, speed, damage)
{

}

TimeVariant::Type Kelvin::getType() const {return TimeVariant::Type::KELVIN;}
