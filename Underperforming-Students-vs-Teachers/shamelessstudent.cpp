#include "shamelessstudent.h"

const QString ShamelessStudent::DEFAULT_NAME = "Shameless Student";

ShamelessStudent::ShamelessStudent(QLabel* widget, Row* row, QString name, int maxHp, int skillSpeed, int cost)
    : SupportStudent(widget, row, name, maxHp, skillSpeed, cost)
{

}

TimeVariant::Type ShamelessStudent::getType() const {return TimeVariant::Type::SHAMELESS_STUDENT;}

//the implementation of the pure virtual update()
void ShamelessStudent::update() {}
