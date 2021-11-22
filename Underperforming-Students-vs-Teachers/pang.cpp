#include "pang.h"

const QString Pang::DEFAULT_NAME = "Pang";

QPixmap* Pang::PIC_0 = nullptr;
QPixmap* Pang::PIC_1 = nullptr;


Pang::Pang(QLabel *widget, Row* row,QString name, int maxHp, int speed, int damage) :
    Teacher(widget, row, name, maxHp, speed, damage)
{

}

TimeVariant::Type Pang::getType() const {return TimeVariant::Type::PANG;}

