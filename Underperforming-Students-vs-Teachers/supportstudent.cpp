#include "supportstudent.h"

SupportStudent::SupportStudent(QLabel* widget, QString name, int maxHp, double skillSpeed, int cost)
    : Student(widget, name, maxHp, skillSpeed, cost)
{

}

TimeVariant::Category SupportStudent::getCategory() const {return TimeVariant::Category::SUPPORT_STUDENT;}
