#include "gbusstudent.h"

const QString GbusStudent::DEFAULT_NAME = "GBUS Student";

QPixmap* GbusStudent::PIC_0 = nullptr;
QPixmap* GbusStudent::PIC_1 = nullptr;
QPixmap* GbusStudent::PIC_2 = nullptr;

GbusStudent::GbusStudent(QLabel* widget, Row* row, QString name, int maxHp, int skillSpeed, int cost)
    : SupportStudent(widget, row, name, maxHp, skillSpeed, cost)
{

}

TimeVariant::Type GbusStudent::getType() const {return TimeVariant::Type::GBUS_STUDENT;}

//the implementation of the pure virtual update()
void GbusStudent::update()
{

}
