#include "shamelessstudent.h"

const QString ShamelessStudent::DEFAULT_NAME = "Shameless Student";

ShamelessStudent::ShamelessStudent(QLabel* widget, QString name, int maxHp, double skillSpeed, int cost)
    : SupportStudent(widget, name, maxHp, skillSpeed, cost)
{

}

TimeVariant::Type ShamelessStudent::getType() const {return TimeVariant::Type::SHAMELESS_STUDENT;}


//the implementation of the pure virtual skill()
void ShamelessStudent::skill() {}

//the implementation of the pure virtual update()
void ShamelessStudent::update() {}
