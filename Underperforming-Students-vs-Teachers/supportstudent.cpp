#include "supportstudent.h"

SupportStudent::SupportStudent(QLabel* widget, Row* row, QString name, int maxHp, double skillSpeed, int cost)
    : Student(widget, row, name, maxHp, skillSpeed, cost)
{

}

TimeVariant::Category SupportStudent::getCategory() const {return TimeVariant::Category::SUPPORT_STUDENT;}
