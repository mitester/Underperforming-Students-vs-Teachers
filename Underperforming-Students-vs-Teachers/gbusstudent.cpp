#include "gbusstudent.h"

const QString GbusStudent::DEFAULT_NAME = "GBUS Student";

GbusStudent::GbusStudent(QLabel* widget, Row* row, QString name, int maxHp, double skillSpeed, int cost)
    : SupportStudent(widget, row, name, maxHp, skillSpeed, cost)
{

}

TimeVariant::Type GbusStudent::getType() const {return TimeVariant::Type::GBUS_STUDENT;}

//the implementation of the pure virtual update()
void GbusStudent::update() {}
