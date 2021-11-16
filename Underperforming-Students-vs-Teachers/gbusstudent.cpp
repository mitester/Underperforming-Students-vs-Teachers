#include "gbusstudent.h"

const QString GbusStudent::DEFAULT_NAME = "GBUS Student";

GbusStudent::GbusStudent(QLabel* widget, QString name, int maxHp, double skillSpeed, int cost)
    : SupportStudent(widget, name, maxHp, skillSpeed, cost)
{

}

TimeVariant::Type GbusStudent::getType() const {return TimeVariant::Type::GBUS_STUDENT;}

//the implementation of the pure virtual update()
void GbusStudent::update() {}
