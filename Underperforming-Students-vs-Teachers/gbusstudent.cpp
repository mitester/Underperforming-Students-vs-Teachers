#include "gbusstudent.h"

const QString GbusStudent::DEFAULT_NAME = "GBUS Student";

GbusStudent::GbusStudent(QWidget* widget, QString name, int maxHp, double skillSpeed, int cost)
    : SupportStudent(widget, name, maxHp, skillSpeed, cost)
{

}

//the implementation of the pure virtual skill()
void GbusStudent::skill() {}

//the implementation of the pure virtual update()
void GbusStudent::update() {}
